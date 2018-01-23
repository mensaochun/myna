/*!
*  Copyright (c) 2015 by hgaolbb
* \file net.cpp
* \brief net
*/

#include "../include/net.hpp"

namespace mini_net {

void NetParam::readNetParam(std::string file) {
    std::ifstream ifs;
    ifs.open(file);
    assert(ifs.is_open());
    Json::Reader reader;
    Json::Value value;
    if (reader.parse(ifs, value)) {
        if (!value["train"].isNull()) {
            auto &tparam = value["train"];
            this->lr = tparam["learning rate"].asDouble();
            this->lr_decay = tparam["lr decay"].asDouble();
            this->update = tparam["update method"].asString();
            this->momentum = tparam["momentum parameter"].asDouble();
            this->num_epochs = tparam["num epochs"].asInt();
            this->use_batch = tparam["use batch"].asBool();
            this->batch_size = tparam["batch size"].asInt();
            this->reg = tparam["reg"].asDouble();
            this->acc_frequence = tparam["acc frequence"].asInt();
            this->acc_update_lr = tparam["frequence update"].asBool();
        }
        if (!value["net"].isNull()) {
            auto &nparam = value["net"];
            for (int i = 0; i < (int)nparam.size(); ++i) {
                auto &ii = nparam[i];
                this->layers.push_back(ii["name"].asString());
                this->ltypes.push_back(ii["type"].asString());
                if (ii["type"].asString() == "Conv") {
                    int num = ii["kernel num"].asInt();
                    int width = ii["kernel width"].asInt();
                    int height = ii["kernel height"].asInt();
                    int pad = ii["pad"].asInt();
                    int stride = ii["stride"].asInt();
                    this->params[ii["name"].asString()].setConvParam(stride, pad, width, height, num);
                }
                if (ii["type"].asString() == "Pool") {
                    int stride = ii["stride"].asInt();
                    int width = ii["kernel width"].asInt();
                    int height = ii["kernel height"].asInt();
                    this->params[ii["name"].asString()].setPoolParam(stride, width, height);
                }
                if (ii["type"].asString() == "Fc") {
                    int num = ii["kernel num"].asInt();
                    this->params[ii["name"].asString()].fc_kernels = num;
                }
            }
        }
    }
}

void Net::trainNet(shared_ptr<Blob>& X,
                    shared_ptr<Blob>& Y,
                    NetParam& param,
                    std::string mode) {
    /*! fill X, Y */
    data_[layers_[0]][0] = X;
    data_[layers_.back()][1] = Y;

    // debug
    Blob pb, pd;

    /*! forward */
    int n = ltype_.size();
    for (int i = 0; i < n-1; ++i) {
        std::string ltype = ltype_[i];
        std::string lname = layers_[i];
        shared_ptr<Blob> out;
        if (ltype == "Conv") {
            int tF = param.params[lname].conv_kernels;
            int tC = data_[lname][0]->get_C();
            int tH = param.params[lname].conv_height;
            int tW = param.params[lname].conv_width;
            if (!data_[lname][1]) {
                data_[lname][1].reset(new Blob(tF, tC, tH, tW, TRANDN));
                (*data_[lname][1]) *= 1e-2;
            }
            if (!data_[lname][2]) {
                data_[lname][2].reset(new Blob(tF, 1, 1, 1, TRANDN));
                (*data_[lname][2]) *= 1e-1;
            }
            ConvLayer::forward(data_[lname], out, param.params[lname]);
        }
        if (ltype == "Pool") {
            PoolLayer::forward(data_[lname], out, param.params[lname]);
            pb = *data_[lname][0];
        }
        if (ltype == "Fc") {
            int tF = param.params[lname].fc_kernels;
            int tC = data_[lname][0]->get_C();
            int tH = data_[lname][0]->get_H();
            int tW = data_[lname][0]->get_W();
            if (!data_[lname][1]) {
                data_[lname][1].reset(new Blob(tF, tC, tH, tW, TRANDN));
                (*data_[lname][1]) *= 1e-2;
            }
            if (!data_[lname][2]) {
                data_[lname][2].reset(new Blob(tF, 1, 1, 1, TRANDN));
                (*data_[lname][2]) *= 1e-1;
            }
            AffineLayer::forward(data_[lname], out);
        }
        if (ltype == "Relu")
            ReluLayer::forward(data_[lname], out);
        if (ltype == "Dropout")
            DropoutLayer::forward(data_[lname], out, param.params[lname]);
        data_[layers_[i+1]][0] = out;
    }

    // calc loss
    std::string loss_type = ltype_.back();
    shared_ptr<Blob> dout;
    if (loss_type == "SVM")
        SVMLossLayer::go(data_[layers_.back()], loss_, dout);
    if (loss_type == "Softmax")
        SoftmaxLossLayer::go(data_[layers_.back()], loss_, dout);
    grads_[layers_.back()][0] = dout;

    loss_history_.push_back(loss_);

    if (mode == "forward")
        return;

    /*! backward */
    for (int i = n-2; i >= 0; --i) {
        std::string ltype = ltype_[i];
        std::string lname = layers_[i];
        if (ltype == "Conv")
            ConvLayer::backward(grads_[layers_[i+1]][0], data_[lname],
                                grads_[lname], param.params[lname]);
        if (ltype == "Pool") {
            PoolLayer::backward(grads_[layers_[i+1]][0], data_[lname],
                                grads_[lname], param.params[lname]);
        }
        if (ltype == "Fc")
            AffineLayer::backward(grads_[layers_[i+1]][0], data_[lname], grads_[lname]);
        if (ltype == "Relu")
            ReluLayer::backward(grads_[layers_[i+1]][0], data_[lname], grads_[lname]);
    }

    // regularition
    double reg_loss = 0;
    for (auto i : layers_) {
        if (grads_[i][1]) {
            // it's ok?
            Blob reg_data = param.reg * (*data_[i][1]);
            (*grads_[i][1]) = (*grads_[i][1]) + reg_data;
            reg_loss += data_[i][1]->sum();
        }
    }
    reg_loss *= param.reg * 0.5;
    loss_ = loss_ + reg_loss;

    return;
}

void Net::testNet(NetParam& param) {
    shared_ptr<Blob> X_batch(new Blob(X_train_->subBlob(0, 1)));
    shared_ptr<Blob> Y_batch(new Blob(Y_train_->subBlob(0, 1)));
    trainNet(X_batch, Y_batch, param);
    cout << "BEGIN TEST LAYERS" << endl;
    for (int i = 0; i < (int)layers_.size(); ++i) {
        testLayer(param, i);
        printf("\n");
    }
}

void Net::initNet(NetParam& param,
                  vector<shared_ptr<Blob>>& X,
                  vector<shared_ptr<Blob>>& Y) {

    layers_ = param.layers;
    ltype_ = param.ltypes;
    for (int i = 0; i < (int)layers_.size(); ++i) {
        data_[layers_[i]] = vector<shared_ptr<Blob>>(3);
        grads_[layers_[i]] = vector<shared_ptr<Blob>>(3);
        step_cache_[layers_[i]] = vector<shared_ptr<Blob>>(3);
        best_model_[layers_[i]] = vector<shared_ptr<Blob>>(3);
    }
    X_train_ = X[0];
    Y_train_ = Y[0];
    X_val_ = X[1];
    Y_val_ = Y[1];

    return;
}

void Net::train(NetParam& param) {
    // to be delete
    int N = X_train_->get_N();
    int iter_per_epochs;
    if (param.use_batch) {
        iter_per_epochs = N / param.batch_size;
    }
    else {
        iter_per_epochs = N;
    }
    int num_iters = iter_per_epochs * param.num_epochs;
    int epoch = 0;

    // iteration
    for (int iter = 0; iter < num_iters; ++iter) {
        // batch
        shared_ptr<Blob> X_batch;
        shared_ptr<Blob> Y_batch;
        if (param.use_batch) {
            // deep copy
            X_batch.reset(new Blob(X_train_->subBlob((iter * param.batch_size) % N,
                                                        ((iter+1) * param.batch_size) % N)));
            Y_batch.reset(new Blob(Y_train_->subBlob((iter * param.batch_size) % N,
                                                        ((iter+1) * param.batch_size) % N)));
        }
        else {
            shared_ptr<Blob> X_batch = X_train_;
            shared_ptr<Blob> Y_batch = Y_train_;
        }

        // train
        trainNet(X_batch, Y_batch, param);

        // update
        for (int i = 0; i < (int)layers_.size(); ++i) {
            std::string lname = layers_[i];
            if (!data_[lname][1] || !data_[lname][2]) {
                continue;
            }
            for (int j = 1; j <= 2; ++j) {
                assert(param.update == "momentum" ||
                       param.update == "rmsprop" ||
                       param.update == "adagrad" ||
                       param.update == "sgd");
                shared_ptr<Blob> dx(new Blob(data_[lname][j]->size()));
                if (param.update == "sgd") {
                    *dx = -param.lr * (*grads_[lname][j]);
                }
                if (param.update == "momentum") {
                    if (!step_cache_[lname][j]) {
                        step_cache_[lname][j].reset(new Blob(data_[lname][j]->size(), TZEROS));
                    }
                    Blob ll = param.momentum * (*step_cache_[lname][j]);
                    Blob rr = param.lr * (*grads_[lname][j]);
                    *dx = ll - rr;
                    step_cache_[lname][j] = dx;
                }
                if (param.update == "rmsprop") {
                    // change it self
                    double decay_rate = 0.99;
                    if (!step_cache_[lname][j]) {
                        step_cache_[lname][j].reset(new Blob(data_[lname][j]->size(), TZEROS));
                    }
                    Blob r1 = decay_rate * (*step_cache_[lname][j]);
                    Blob r2 = (1 - decay_rate) * (*grads_[lname][j]);
                    Blob r3 = r2 * (*grads_[lname][j]);
                    *step_cache_[lname][j] = r1 + r3;
                    Blob d1 = (*step_cache_[lname][j]) + 1e-8;
                    Blob u1 = param.lr * (*grads_[lname][j]);
                    Blob d2 = mini_net::sqrt(d1);
                    Blob r4 = u1 / d2;
                    *dx = 0 - r4;
                }
                if (param.update == "adagrad") {
                    if (!step_cache_[lname][j]) {
                        step_cache_[lname][j].reset(new Blob(data_[lname][j]->size(), TZEROS));
                    }
                    *step_cache_[lname][j] = (*grads_[lname][j]) * (*grads_[lname][j]);
                    Blob d1 = (*step_cache_[lname][j]) + 1e-8;
                    Blob u1 = param.lr * (*grads_[lname][j]);
                    Blob d2 = mini_net::sqrt(d1);
                    Blob r4 = u1 / d2;
                    *dx = 0 - r4;
                }
                *data_[lname][j] = (*data_[lname][j]) + (*dx);
            }
        }

        // evaluate
        bool first_it = (iter == 0);
        bool epoch_end = (iter + 1) % iter_per_epochs == 0;
        bool acc_check = (param.acc_frequence && (iter+1) % param.acc_frequence == 0);
        if (first_it || epoch_end || acc_check) {
            // update learning rate[TODO]
            if ((iter > 0 && epoch_end) || param.acc_update_lr) {
                param.lr *= param.lr_decay;
                if (epoch_end) {
                    epoch++;
                }
            }

            // evaluate train set accuracy
            shared_ptr<Blob> X_train_subset;
            shared_ptr<Blob> Y_train_subset;
            if (N > 1000) {
                X_train_subset.reset(new Blob(X_train_->subBlob(0, 100)));
                Y_train_subset.reset(new Blob(Y_train_->subBlob(0, 100)));
            }
            else {
                X_train_subset = X_train_;
                Y_train_subset = Y_train_;
            }
            trainNet(X_train_subset, Y_train_subset, param, "forward");
            double train_acc = prob(*data_[layers_.back()][1], *data_[layers_.back()][0]);
            train_acc_history_.push_back(train_acc);

            // evaluate val set accuracy[TODO: change train to val]
            trainNet(X_val_, Y_val_, param, "forward");
            double val_acc = prob(*data_[layers_.back()][1], *data_[layers_.back()][0]);
            val_acc_history_.push_back(val_acc);

            // print
            printf("iter: %d  loss: %f  train_acc: %0.2f%%    val_acc: %0.2f%%    lr: %0.6f\n",
                    iter, loss_, train_acc*100, val_acc*100, param.lr);

            // save best model[TODO]
            //if (val_acc_history_.size() > 1 && val_acc < val_acc_history_[val_acc_history_.size()-2]) {
            //    for (auto i : layers_) {
            //        if (!data_[i][1] || !data_[i][2]) {
            //            continue;
            //        }
            //        best_model_[i][1] = data_[i][1];
            //        best_model_[i][2] = data_[i][2];
            //    }
            //}
        }
    }

    return;
}


void Net::testLayer(NetParam& param, int lnum) {
    std::string ltype = ltype_[lnum];
    std::string lname = layers_[lnum];
    if (ltype == "Fc")
        _test_fc_layer(data_[lname], grads_[lname], grads_[layers_[lnum+1]][0]);
    if (ltype == "Conv")
        _test_conv_layer(data_[lname], grads_[lname], grads_[layers_[lnum+1]][0], param.params[lname]);
    if (ltype == "Pool")
        _test_pool_layer(data_[lname], grads_[lname], grads_[layers_[lnum+1]][0], param.params[lname]);
    if (ltype == "Relu")
        _test_relu_layer(data_[lname], grads_[lname], grads_[layers_[lnum+1]][0]);
    if (ltype == "Dropout")
        _test_dropout_layer(data_[lname], grads_[lname], grads_[layers_[lnum+1]][0], param.params[lname]);
    if (ltype == "SVM")
        _test_svm_layer(data_[lname], grads_[lname][0]);
    if (ltype == "Softmax")
        _test_softmax_layer(data_[lname], grads_[lname][0]);
}

void Net::_test_fc_layer(vector<shared_ptr<Blob>>& in,
                         vector<shared_ptr<Blob>>& grads,
                         shared_ptr<Blob>& dout) {

    auto nfunc =[in](shared_ptr<Blob>& e) {return AffineLayer::forward(in, e); };
    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);
    Blob num_dw = Test::calcNumGradientBlob(in[1], dout, nfunc);
    Blob num_db = Test::calcNumGradientBlob(in[2], dout, nfunc);

    cout << "Test Affine Layer:" << endl;
    cout << "Test num_dx and dX Layer:" << endl;
    cout << Test::relError(num_dx, *grads[0]) << endl;
    cout << "Test num_dw and dW Layer:" << endl;
    cout << Test::relError(num_dw, *grads[1]) << endl;
    cout << "Test num_db and db Layer:" << endl;
    cout << Test::relError(num_db, *grads[2]) << endl;

    return;
}

void Net::_test_conv_layer(vector<shared_ptr<Blob>>& in,
                     vector<shared_ptr<Blob>>& grads,
                     shared_ptr<Blob>& dout,
                     Param& param)  {

    auto nfunc =[in, &param](shared_ptr<Blob>& e) {return ConvLayer::forward(in, e, param); };
    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);
    Blob num_dw = Test::calcNumGradientBlob(in[1], dout, nfunc);
    Blob num_db = Test::calcNumGradientBlob(in[2], dout, nfunc);

    cout << "Test Conv Layer:" << endl;
    cout << "Test num_dx and dX Layer:" << endl;
    cout << Test::relError(num_dx, *grads[0]) << endl;
    cout << "Test num_dw and dW Layer:" << endl;
    cout << Test::relError(num_dw, *grads[1]) << endl;
    cout << "Test num_db and db Layer:" << endl;
    cout << Test::relError(num_db, *grads[2]) << endl;

    return;
}
void Net::_test_pool_layer(vector<shared_ptr<Blob>>& in,
                     vector<shared_ptr<Blob>>& grads,
                     shared_ptr<Blob>& dout,
                     Param& param) {
    auto nfunc =[in, &param](shared_ptr<Blob>& e) {return PoolLayer::forward(in, e, param); };

    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);

    cout << "Test Pool Layer:" << endl;
    cout << Test::relError(num_dx, *grads[0]) << endl;

    return;
}

void Net::_test_relu_layer(vector<shared_ptr<Blob>>& in,
                     vector<shared_ptr<Blob>>& grads,
                     shared_ptr<Blob>& dout) {
    auto nfunc =[in](shared_ptr<Blob>& e) {return ReluLayer::forward(in, e); };
    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);

    cout << "Test ReLU Layer:" << endl;
    cout << Test::relError(num_dx, *grads[0]) << endl;

    return;
}

void Net::_test_dropout_layer(vector<shared_ptr<Blob>>& in,
                     vector<shared_ptr<Blob>>& grads,
                     shared_ptr<Blob>& dout,
                     Param& param) {
    shared_ptr<Blob> dummy_out;
    auto nfunc =[in, &param](shared_ptr<Blob>& e) {return DropoutLayer::forward(in, e, param); };

    cout << "Test Dropout Layer:" << endl;
    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);
    cout << Test::relError(num_dx, *grads[0]) << endl;

    return;
}

void Net::_test_svm_layer(vector<shared_ptr<Blob>>& in,
                     shared_ptr<Blob>& dout) {
    shared_ptr<Blob> dummy_out;
    auto nfunc =[in, &dummy_out](double& e) {return SVMLossLayer::go(in, e, dummy_out, 1); };
    cout << "Test SVM Loss Layer:" << endl;

    Blob num_dx = Test::calcNumGradientBlobLoss(in[0], nfunc);
    cout << Test::relError(num_dx, *dout) << endl;

    return;
}

void Net::_test_softmax_layer(vector<shared_ptr<Blob>>& in,
                     shared_ptr<Blob>& dout) {
    shared_ptr<Blob> dummy_out;
    auto nfunc =[in, &dummy_out](double& e) {return SoftmaxLossLayer::go(in, e, dummy_out, 1); };

    cout << "Test Softmax Loss Layer:" << endl;
    Blob num_dx = Test::calcNumGradientBlobLoss(in[0], nfunc);
    cout << Test::relError(num_dx, *dout) << endl;

    return;
}


} //namespace mini_net
