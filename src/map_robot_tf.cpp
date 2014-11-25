#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <ras_arduino_msgs/Odometry.h>

void poseCallback(const ras_arduino_msgs::OdometryConstPtr& msg){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(5.0 + msg->x, 5.0 + msg->y, 0) );
  tf::Quaternion q;
  q.setEuler(0.0, 0.0, msg->theta);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "robot_center"));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "map_robot_tf_broadcaster");

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/arduino/odometry", 1, &poseCallback);

  ros::spin();
  return 0;
}
