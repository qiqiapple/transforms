#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <math.h>

int main(int argc, char **argv) {

    ros::init(argc, argv, "map_base_tf");

    ros::NodeHandle n;

    static tf::TransformBroadcaster br;
    tf::Transform transform;

    ros::Rate loop_rate(20.0);
    while (n.ok()) {
        transform.setOrigin(tf::Vector3(5.0, 5.0, 0.0));
        tf::Quaternion q;
        q.setEuler(0.0, M_PI, 0.0);
        transform.setRotation(q);

        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "base"));
        loop_rate.sleep();
    }

    return 0;
}
