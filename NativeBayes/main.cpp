

#include <cstdio>

#include <Windows.h>

#include "LBayesClassifier.h"

int main()
{
    // 定义样本矩阵
    // 每一行代表一个人
    // 第一列为身高(英尺), 第二列为体重(磅), 第3列为脚掌(英寸)
    int dataList[24] = 
    {
        600, 180, 12,
        592, 190, 11,
        558, 170, 12,
        592, 165, 10,
        500, 100, 6,
        550, 150, 8,
        542, 130, 7,
        575, 150, 9
    };
    LBayesMatrix sampleMatrix(8, 3, dataList);

    // 定义样本的类别向量
    // 1: 男
    // 0: 女
    int classList[8] = 
    {
        1,
        1,
        1,
        1,
        0,
        0,
        0,
        0
    };
    LBayesMatrix classVector(8, 1, classList);

    // 定义贝叶斯原始问题
    LBayesProblem problem(sampleMatrix, classVector, BAYES_FEATURE_CONTINUS);

    // 定义贝叶斯分类器, 并且训练
    LBayesClassifier classifier;
    classifier.TrainModel(problem);

    
    // 输入新样本, 并预测新样本的类别
    LBayesMatrix newSample(1, 3);
    newSample[0][0] = 600; newSample[0][1] = 130; newSample[0][2] = 8;
    
    int predictValue = -1; 
    classifier.Predict(newSample, &predictValue);

    printf("%d\n", predictValue);
    system("pause");
    return 0;
}