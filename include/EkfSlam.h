#ifndef PROJECT_EKFSLAM_H
#define PROJECT_EKFSLAM_H

#include <Eigen/Dense>
#include <pcl/point_cloud.h>
#include "ScanBuilder.h"

class EkfSlam {

public:
    EkfSlam();

    /*
        predict step in EKF slam 
        @dis displacement between two data
        @q quatenrnion
        @det_t time between two data
        @return nothing 
    */
    void predict(Eigen::Vector2d dis, Eigen::Quaterniond q, double det_t);

    /*
        update step in EKF slam 
        @cloud_pair cloud and its origin
        @return nothing 
    */
    void update(CloudPair cloud_pair);

    Eigen::Vector2d get_current_state() {
        Eigen::Vector2d pos;
        pos[0] = state_[0];
        pos[1] = state_[1];

        return pos;
    }

    /*
        get transformed cloud 
        @return nothing 
    */
    pcl::PointCloud<pcl::PointXYZ> get_cloud();

    void init(Eigen::Vector2d pos){
        state_[0] = pos[0];
        state_[1] = pos[1];
        state_[2] = 0.0;
    }

private:
    Eigen::Vector3d merge_predict(Eigen::Vector2d dis, Eigen::Quaterniond q);

    void filter(pcl::PointCloud<pcl::PointXYZ>& cloud);

    std::vector<int> search_nearest();

    Eigen::Vector2d icp(int ref, double& sigma);

    Eigen::VectorXd state_;
    Eigen::MatrixXd covariance_;

    Eigen::Matrix3d predict_covariance_;

    std::vector<pcl::PointCloud<pcl::PointXYZ>> cloud_vec_;

    unsigned int num_;
};


#endif //PROJECT_EKFSLAM_H
