/*!
*  Copyright (c) 2015 by hgaolbb
* \file net.hpp
* \brief 
*/

#ifndef MINI_NET_NET_HPP_
#define MINI_NET_NET_HPP_

#include "blob.hpp"
#include "layer.hpp"
#include "test.hpp"
#include <json/json.h>
#include <unordered_map>
#include <fstream>

using std::unordered_map;
using std::shared_ptr;

namespace mini_net {

struct NetParam {
    /*! methods of update net parameters, sgd/momentum/... */
    std::string update;
    /*! learning rate */
    double lr;
    double lr_decay;
    /*! momentum parameter */
    double momentum;
    int num_epochs;
    /*! whether use batch size */
    bool use_batch;
    int batch_size;
    /*! regulazation parameter */
    double reg;
    /*! \brief acc_frequence, how many iterations to check val_acc and train_acc */
    int acc_frequence;
    bool acc_update_lr;

    vector<std::string> layers;
    vector<std::string> ltypes;
    unordered_map<std::string, Param> params;

    void readNetParam(std::string file);
};

class Net {

public:
    Net(){}

    /*! \brief forward and backward */
    void trainNet(shared_ptr<Blob>& X, 
                  shared_ptr<Blob>& Y,
                  NetParam& param,
                  std::string mode = "fb");

    /*! \brief test if all layers are right, be careful set reg to 0 */
    void testNet(NetParam& param);

    /*!
     * \brief set input data and ground truth
     * \param[in]  NetParam& param                   net parameters
     * \param[in]  vector<shared_ptr<Blob>>& X       X[0]: train data,  X[1]: val data
     * \param[in]  vector<shared_ptr<Blob>>& Y       Y[0]: train label, Y[1]: val label
     */
    void initNet(NetParam& param,
                 vector<shared_ptr<Blob>>& X,
                 vector<shared_ptr<Blob>>& Y);

    /*! \brief train the net */
    void train(NetParam& param);

    //void sampleInitData();

    /*! test num_grads of lnum th layer */
    void testLayer(NetParam& param, int lnum);

private:

    void _test_fc_layer(vector<shared_ptr<Blob>>& in,
                        vector<shared_ptr<Blob>>& grads,
                        shared_ptr<Blob>& dout); 

    void _test_conv_layer(vector<shared_ptr<Blob>>& in,
                         vector<shared_ptr<Blob>>& grads,
                         shared_ptr<Blob>& dout,
                         Param& param); 

    void _test_pool_layer(vector<shared_ptr<Blob>>& in,
                         vector<shared_ptr<Blob>>& grads,
                         shared_ptr<Blob>& dout,
                         Param& param); 

    void _test_relu_layer(vector<shared_ptr<Blob>>& in,
                         vector<shared_ptr<Blob>>& grads,
                         shared_ptr<Blob>& dout); 

    void _test_dropout_layer(vector<shared_ptr<Blob>>& in,
                         vector<shared_ptr<Blob>>& grads,
                         shared_ptr<Blob>& dout,
                         Param& param); 

    void _test_svm_layer(vector<shared_ptr<Blob>>& in,
                         shared_ptr<Blob>& dout); 

    void _test_softmax_layer(vector<shared_ptr<Blob>>& in,
                         shared_ptr<Blob>& dout); 

    /*! \brief save data names */
    vector<std::string> layers_;
    /*! \brief save data types */
    vector<std::string> ltype_;
    /*! \brief temporary loss score */
    double loss_;
    // train data set
    shared_ptr<Blob> X_train_;
    shared_ptr<Blob> Y_train_;
    // val data set
    shared_ptr<Blob> X_val_;
    shared_ptr<Blob> Y_val_;
    
    unordered_map<std::string, vector<shared_ptr<Blob>>> data_;
    unordered_map<std::string, vector<shared_ptr<Blob>>> grads_;
    unordered_map<std::string, vector<shared_ptr<Blob>>> num_grads_;

    /*! train or test */
    std::string type_;

    /*! train result */
    vector<double> loss_history_;
    vector<double> train_acc_history_;
    vector<double> val_acc_history_;

    /*! step cache */
    unordered_map<std::string, vector<shared_ptr<Blob>>> step_cache_;

    /*! \brief best model */
    unordered_map<std::string, vector<shared_ptr<Blob>>> best_model_;

}; // class Net

} // namespace mini_net

#endif
