#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <math.h>

int main(int argc, char **argv) {

    ros::init(argc, argv, "map_base_tf");

    ros::NodeHandle n;

    static tf::TransformBroadcaster br;
    tf::Transform transform;

    ros::Rate loop_rate(10.0);
    while (n.ok()) {
        transform.setOrigin(tf::Vector3(50.0, 50.0, 0.0));
        transform.setRotation(tf::Quaternion(0, 0, 0, 1));

        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "base"));
        loop_rate.sleep();
    }

    return 0;
}
