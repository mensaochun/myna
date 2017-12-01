
#include <iostream>
#include <armadillo>
#include <../include/mini_net.hpp>

using namespace arma;
using namespace mini_net;
using std::shared_ptr;

//
//void testSharedptr() {
//    shared_ptr<int> pp(new int(1));
//    cout << *pp << endl;
//    //pp.reset();
//    //cout << *pp << endl;
//}
//
//void testArma() {
//    /*! test randn/randu seed */
//    //arma_rng::set_seed(123);
//    arma_rng::set_seed_random();
//    cube cca(5,5,1,fill::randn);
//    cca.print();
//    //arma_rng::set_seed(123);
//    arma_rng::set_seed_random();
//    cube ccb(5,5,1,fill::randn);
//    ccb.print();
//    /*! test cude/vec/mat to blob */
//    vec va = linspace(1, 12, 12);
//    va.print();
//    vectorise(va).print();
//    mat mma = reshape(va, 2,6);
//    mma.print();
//    // A * B, run!
//    mat A = randu<mat>(5, 10);
//    mat B = randu<mat>(10, 5);
//    mat C = A * B;
//    C.print();
//    // mat2blob
//    mat mc(2,8,fill::randu);
//    mc.print();
//    //mc = mc.t();
//    //mc.print();
//    //cube cb = cube(mc.colptr(0), 2, 2, 3);
//    //cb.print();
//    Blob *bc = NULL;
//    //mat2Blob(mc, &bc, 2,2,2);
//    // vectorisze
//    cube ca(2,2,2,fill::ones);
//    ca *= 2;
//    ca.print();
//    mat mb = reshape(vectorise(ca), 4, 2);
//    mb.print();
//
//    mat ma(4,2,fill::ones);
//    ma *= 0.5;
//    //cout << vectorise(ma) << endl;
//    cout << accu(vectorise(ma) % vectorise(ca)) << endl;
//   
//    //
//    cube a(2,2,2);
//    a.print();
//    cout << a(0,0,0) << endl;
//    a(0,0,1) = 1;
//    cout << a(0,0,1);
//}
//
//void testBlob() {
//    /*! random problem */
//    Blob aaa(4,2,2,2,TRANDN);
//    aaa.reshape().print();
//    Blob aab(4,2,2,2,TRANDU);
//    aab.reshape().print();
//    /*! test pad() */
//    Blob oa(2,2,2,2,TONES);
//    oa.pad(1, 0).print();
//
//    /*! test sum() abs()*/
//    oa.print();
//    oa.max(0.5).print();
//    Blob oc(2,2,2,2,TRANDN);
//    oc.print();
//    oc.abs().print();
//    cout << oc.maxVal() << endl;
//
//    /*! test operation */
//    Blob ob(2,2,2,2,TONES);
//    (oa - ob)[0].print();
//    (oa + ob)[0].print();
//    (oa * ob)[0].print();
//    (oa / ob)[0].print();
//
//    // check sum()
//    Blob aa(2,2,2,2,TONES);
//    cout << aa.sum();
//
//    // reshape
//    Blob pc(5,2,2,2,TONES);
//    mat mc = pc.reshape();
//    cout << "row: " << mc.n_rows << "\t" << "col: " << mc.n_cols << endl;
//    mc.print();
//
//    // ptr
//    Blob *pa = new Blob(5,2,2,1,TONES);
//    (*pa)[0].print();
//    Blob *pb = new Blob(5,2,2,2,TDEFAULT);
//    (*pb)[0].print();
//
//    // += -= *= /+
//    Blob a(2,3,2,2,TONES);
//    a[0].print("a[0] = \n");
//    a += 0.5;
//    a[0].print("a[0] = \n");
//    a -= 0.5;
//    a[0].print("a[0] = \n");
//    a *= 2;
//    a[0].print("a[0] = \n");
//    a /= 2;
//    a[0].print("a[0] = \n");
//
//    return;
//}

void testAffineLayer() {
    shared_ptr<Blob> a(new Blob(5,3,2,2,TONES));
    shared_ptr<Blob> b(new Blob(10,3,2,2,TONES));
    shared_ptr<Blob> c(new Blob(10,1,1,1,TONES));
    shared_ptr<Blob> dout(new Blob(5,10,1,1,TRANDN));
    vector<shared_ptr<Blob>> in{a, b, c};
    shared_ptr<Blob> out;
    vector<shared_ptr<Blob>> grads(3, shared_ptr<Blob>());
    AffineLayer::backward(dout, in, grads);
    auto nfunc =[in](shared_ptr<Blob>& e) {return AffineLayer::forward(in, e);};
    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);
    Blob num_dw = Test::calcNumGradientBlob(in[1], dout, nfunc);
    Blob num_db = Test::calcNumGradientBlob(in[2], dout, nfunc);

    cout << "test affine layer" << endl;
    cout << Test::relError(num_dx, *grads[0]) << endl;
    cout << Test::relError(num_dw, *grads[1]) << endl;
    cout << Test::relError(num_db, *grads[2]) << endl;

    return;
}

void testConvLayer() {
    shared_ptr<Blob> x(new Blob(1,3,5,5,TRANDN));
    shared_ptr<Blob> w(new Blob(2,3,3,3,TRANDN));
    shared_ptr<Blob> b(new Blob(2,1,1,1,TRANDN));
    shared_ptr<Blob> dout(new Blob(1,2,5,5,TRANDN));
    Param param;
    param.setConvParam(1,1,3,3,5);
    vector<shared_ptr<Blob>> in{x, w, b};
    vector<shared_ptr<Blob>> grads(3, shared_ptr<Blob>());
    grads.push_back(shared_ptr<Blob>());
    grads.push_back(shared_ptr<Blob>());
    grads.push_back(shared_ptr<Blob>());
    ConvLayer::backward(dout, in, grads, param);

    /*! test num_grads */
    auto nfunc =[in, &param](shared_ptr<Blob>& e) {return ConvLayer::forward(in, e, param);};
    cout << "test conv layer" << endl;
    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);
    Blob num_dw = Test::calcNumGradientBlob(in[1], dout, nfunc);
    Blob num_db = Test::calcNumGradientBlob(in[2], dout, nfunc);

    cout << Test::relError(num_dx, *grads[0]) << endl;
    cout << Test::relError(num_dw, *grads[1]) << endl;
    cout << Test::relError(num_db, *grads[2]) << endl;

    return;
}

void testPoolLayer() {
    shared_ptr<Blob> x(new Blob(1,5,4,4,TRANDN));
    //shared_ptr<Blob> x(new Blob(1,5,4,4,TZEROS));
    (*x) *= 1e-2;
    shared_ptr<Blob> dout(new Blob(1,5,2,2,TRANDN));
    vector<shared_ptr<Blob>> in{x};
    shared_ptr<Blob> out;
    Param param;
    param.setPoolParam(2,2,2);
    PoolLayer::forward(in, out, param);
    vector<shared_ptr<Blob>> grads(3, shared_ptr<Blob>());
    PoolLayer::backward(dout, in, grads, param);
    auto nfunc =[in, &param](shared_ptr<Blob>& e) {return PoolLayer::forward(in, e, param);};
    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);
    cout << "test pool layer" << endl;
    cout << Test::relError(num_dx, *grads[0]) << endl;
}

void testRelu() {
    shared_ptr<Blob> x(new Blob(1,1,5,5,TRANDN));
    shared_ptr<Blob> dout(new Blob(1,1,5,5,TRANDN));
    vector<shared_ptr<Blob>> in{x};
    shared_ptr<Blob> out;
    vector<shared_ptr<Blob>> grads(3, shared_ptr<Blob>());
    ReluLayer::backward(dout, in, grads);
    auto nfunc =[in](shared_ptr<Blob>& e) {return ReluLayer::forward(in, e);};
    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);
    cout << "test relu layer" << endl;
    cout << Test::relError(num_dx, *grads[0]) << endl;
}

void testDropout() {
    shared_ptr<Blob> x(new Blob(1,1,5,5,TRANDN));
    shared_ptr<Blob> dout(new Blob(1,1,5,5,TRANDN));
    vector<shared_ptr<Blob>> in{x};
    shared_ptr<Blob> out;
    Param param;
    param.setDropoutpParam(3, 0.5, 123);
    vector<shared_ptr<Blob>> grads(3, shared_ptr<Blob>());
    shared_ptr<Blob> dummy_out;
    auto nfunc =[in, &param](shared_ptr<Blob>& e) {return DropoutLayer::forward(in, e, param);};
    Blob num_dx = Test::calcNumGradientBlob(in[0], dout, nfunc);
    DropoutLayer::backward(dout, in, grads, param);
    cout << "test dropout layer" << endl;
    cout << Test::relError(num_dx, *grads[0]) << endl;
}

void testSoftmax() {
    //shared_ptr<Blob> x(new Blob(10,8,1,1,TRANDU));
    shared_ptr<Blob> x(new Blob(50,10,1,1,TRANDN));
    //(*x) *= 100;
    mat aa = randi<mat>(50, 1, distr_param(0,9));
    mat bb(50,10,fill::zeros);
    for (int i = 0; i < 50; ++i) {
        bb(i, (uword)aa(i,0)) = 1;
    }
    shared_ptr<Blob> y;
    mat2Blob(bb, y, x->size());
    vector<shared_ptr<Blob>> in{x, y};
    double loss;
    shared_ptr<Blob> out;
    shared_ptr<Blob> dummy_out;
    auto nfunc =[in, &dummy_out](double& e) {return SoftmaxLossLayer::go(in, e, dummy_out, 1);};
    SoftmaxLossLayer::go(in, loss, out);
    Blob num_dx = Test::calcNumGradientBlobLoss(in[0], nfunc);
    cout << "test softmax layer" << endl;
    cout << Test::relError(num_dx, *out) << endl;
}

void testSVM() {
    shared_ptr<Blob> x(new Blob(10, 8, 1, 1, TRANDU));
    mat aa = randi<mat>(10, 1, distr_param(0, 7));
    mat bb(10, 8, fill::zeros);
    for (int i = 0; i < 10; ++i) {
        bb(i, (uword)aa(i, 0)) = 1;
    }
    shared_ptr<Blob> y;
    mat2Blob(bb, y, x->size());
    vector<shared_ptr<Blob>> in{x, y};
    double loss;
    shared_ptr<Blob> out;
    SVMLossLayer::go(in, loss, out);
    shared_ptr<Blob> dummy_out;
    auto nfunc =[in, &dummy_out](double& e) {return SVMLossLayer::go(in, e, dummy_out, 1);};
    Blob num_dx = Test::calcNumGradientBlobLoss(in[0], nfunc);
    cout << "test svm layer" << endl;
    cout << Test::relError(num_dx, *out) << endl;
}

///*
//void testTest() {
//    /*
//    // check gradient
//    mat x = linspace<mat>(0, 9, 10);
//    mat a(1, 10, fill::ones);
//    mat num_dx = Test::calcNumGradientX(x, Test::test_fcalar, a);
//    x.print();
//    num_dx.print();
//    mat num_da = Test::calcNumGradientA(a, Test::test_fcalar, x);
//    a.print();
//    num_da.print();
//    */
//
//    /*! check gradient mat */
//    // affine layer
//    Blob x(4,2,2,2,TRANDN);
//    Blob w(2,2,2,2,TRANDN);
//    Blob b(2,1,1,1,TRANDN);
//    Blob dout(4,2,1,1,TRANDN);
//    vector<Blob*> in{&x, &w, &b};
//    //Blob *oo = NULL;
//    //w.print();
//    //AffineLayer::forward(in, &oo);
//    Blob num_dx = Test::calcNumGradientBlob(in, &dout, AffineLayer::forward, TDX);
//    Blob num_dw = Test::calcNumGradientBlob(in, &dout, AffineLayer::forward, TDW);
//    Blob num_db = Test::calcNumGradientBlob(in, &dout, AffineLayer::forward, TDB);
//    vector<Blob*> grads;
//    AffineLayer::backward(&dout, in, grads);
//    num_db.print("num_dw:\n");
//    (*grads[2]).print("dw:\n");
//
//    cout << Test::relError(num_dx, *grads[0]) << endl;
//    cout << Test::relError(num_dw, *grads[1]) << endl;
//    cout << Test::relError(num_db, *grads[2]) << endl;
//
//    return;
//}

//void testNet() {
//    Net a;
//    a.initNet();
//    a.sampleNet(0);
//}

void testSampleNetTrain() {
    NetParam param;
    param.batch_size = 30;
    param.lr = 0.1;
    // momentum=0.9, lr_decay=0.99, lr=0.05
    param.momentum = 0.9;
    param.num_epochs = 500;
    /*! when testing num_gradiets, reg must set to 0 */
    param.reg = 0;
    param.update = "momentum";
    param.use_batch = true;
    param.acc_frequence = 1;
    param.lr_decay = 0.99;

    //shared_ptr<Blob> X(new Blob(100, 2, 16, 16, TRANDN));
    shared_ptr<Blob> X(new Blob(100, 2, 8, 8, TRANDN));
    //(*X) *= 100;
    shared_ptr<Blob> Y;
    mat aa = randi<mat>(100, 1, distr_param(0, 9));
    mat bb(100, 10, fill::zeros);
    for (int i = 0; i < 100; ++i) {
        bb(i, (uword)aa(i, 0)) = 1;
    }
    mat2Blob(bb, Y, 10, 1, 1);
    param.layers.push_back("conv1");
    param.params["conv1"].conv_width = 3;
    param.params["conv1"].conv_height = 3;
    param.params["conv1"].conv_pad = 1;
    param.params["conv1"].conv_stride = 1;
    param.params["conv1"].conv_kernels = 5;
    param.layers.push_back("relu1");
    param.layers.push_back("pool1");
    param.params["pool1"].setPoolParam(2,2,2);
    //param.params["pool1"].pool_height = 2;
    //param.params["pool1"].pool_width = 2;
    //param.params["pool1"].pool_stride = 2;
    param.layers.push_back("fc1");
    param.params["fc1"].fc_kernels = 10;
    param.layers.push_back("softmax");
    param.ltypes.push_back("Conv");
    param.ltypes.push_back("Relu");
    param.ltypes.push_back("Pool");
    param.ltypes.push_back("Fc");
    param.ltypes.push_back("Softmax");

    Net inst;
    vector<shared_ptr<Blob>> data{X,X};
    vector<shared_ptr<Blob>> label{Y,Y};
    inst.initNet(param, data, label);
    inst.train(param);
    //inst.testNet(param);
}

int main()
{
    //testSharedptr();
    //testArma();
    //testBlob();
    //testAffineLayer();
    //testConvLayer();
    //testPoolLayer();
    //testRelu();
    //testDropout();
    //testSoftmax();
    //testSVM();
    //testTest();
    //int n = 3;
    //testNet();
    //while (n--) {
    //    mat a(5,5,fill::randn);
    //    a.print("a\n");
    //}
    //Blob b(4,2,2,2,TRANDN);
    //b.reshape().print();
    testSampleNetTrain();

    return 0;
}
