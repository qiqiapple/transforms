#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <math.h>

int main(int argc, char **argv) {

    ros::init(argc, argv, "ir2_tf_broadcaster");

    ros::NodeHandle n;

    static tf::TransformBroadcaster br;
    tf::Transform transform;

    ros::Rate loop_rate(20.0);
    while (n.ok()) {
        transform.setOrigin(tf::Vector3(0.065, 0.06, 0.0));
        //transform.setRotation(tf::Quaternion(0, 0, -M_PI_2, 1));
        tf::Quaternion q;
        q.setEuler(0.0, 0.0, -M_PI_2);
        transform.setRotation(q);

        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "robot_center", "sensor2"));
        loop_rate.sleep();
    }

    return 0;
}
