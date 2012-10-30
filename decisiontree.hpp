  //
  //  decisiontree.hpp
  //  rrf-fs-prototype
  //
  //  Created by Abu Zaher Faridee on 5/28/12.
  //  Copyright (c) 2012 Schloss Lab. All rights reserved.
  //

#ifndef rrf_fs_prototype_decisiontree_hpp
#define rrf_fs_prototype_decisiontree_hpp

#include "macros.h"
#include "rftreenode.hpp"
#include "abstractdecisiontree.hpp"

/***********************************************************************/

struct VariableRankDescendingSorter {
  bool operator() (vector<int> first, vector<int> second){ return first[1] > second[1]; }
};
struct VariableRankDescendingSorterDouble {
    bool operator() (vector<double> first, vector<double> second){ return first[1] > second[1]; }
};
/***********************************************************************/

class DecisionTree: public AbstractDecisionTree{
    
    friend class RandomForest;
    
public:
    
    DecisionTree(vector< vector<int> > baseDataSet,
                 vector<int> globalDiscardedFeatureIndices,
                 OptimumFeatureSubsetSelector optimumFeatureSubsetSelector,
                 string treeSplitCriterion);
    virtual ~DecisionTree(){ deleteTreeNodesRecursively(rootNode); }
    
    int calcTreeVariableImportanceAndError();
    int evaluateSample(vector<int> testSample);
    int calcTreeErrorRate(int& numCorrect, double& treeErrorRate);
    vector< vector<int> > randomlyShuffleAttribute(vector< vector<int> > samples, int featureIndex);  
    void purgeDataSetsFromTree() { purgeTreeNodesDataRecursively(rootNode); }
    int purgeTreeNodesDataRecursively(RFTreeNode* treeNode);
    
    
private:
    
    void buildDecisionTree();
    int splitRecursively(RFTreeNode* rootNode);
    int findAndUpdateBestFeatureToSplitOn(RFTreeNode* node);
    vector<int> selectFeatureSubsetRandomly(vector<int> globalDiscardedFeatureIndices, vector<int> localDiscardedFeatureIndices);
    int printTree(RFTreeNode* treeNode, string caption);
    void deleteTreeNodesRecursively(RFTreeNode* treeNode);
    
    vector<int> variableImportanceList;
    map<int, int> outOfBagEstimates;
};

#endif