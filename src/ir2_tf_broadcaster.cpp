#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <math.h>

int main(int argc, char **argv) {

    ros::init(argc, argv, "ir2_tf_broadcaster");

    ros::NodeHandle n;

    static tf::TransformBroadcaster br;
    tf::Transform transform;

    ros::Rate loop_rate(10.0);
    while (n.ok()) {
        transform.setOrigin(tf::Vector3(6.0, -6.5, 0.0));
        transform.setRotation(tf::Quaternion(0, 0, -M_PI/2, 1));

        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "robot_center", "sensor2"));
        loop_rate.sleep();
    }

    return 0;
}
