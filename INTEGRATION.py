import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray
import random
from std_msgs.msg import String
from nav2_simple_commander.robot_navigator import BasicNavigator, NavigationResult
from geometry_msgs.msg import PoseStamped
from builtin_interfaces.msg import Time
import joblib
import os

class InputNode(Node):
    def __init__(self):
        super().__init__('input_node')
        self.publisher_ = self.create_publisher(Int32MultiArray, 'task_conditions', 10)
        self.timer = self.create_timer(5.0, self.publish_conditions)
        self.get_logger().info('Input Node Started')

    def publish_conditions(self):
        msg = Int32MultiArray()
       
        msg.data = [
            random.randint(0, 2), 
            random.randint(0, 2),  
            random.randint(0, 2)  
        ]
        self.publisher_.publish(msg)
        self.get_logger().info(f'Published: {msg.data}')

class DecisionNode(Node):
    def __init__(self):
        super().__init__('decision_node')
        self.subscription = self.create_subscription(Int32MultiArray, 'task_conditions', self.callback, 10)
        self.publisher_ = self.create_publisher(String, 'next_room', 10)

        model_path = os.path.join(os.getcwd(), 'room_decision_model.joblib')
        self.model = joblib.load(model_path)
        self.get_logger().info('Decision Node Started - Model Loaded')

    def callback(self, msg):
        prediction = self.model.predict([msg.data])[0]
        self.get_logger().info(f'Predicted Room: {prediction}')
        out_msg = String()
        out_msg.data = prediction
        self.publisher_.publish(out_msg)

class NavigatorNode(Node):
    def __init__(self):
        super().__init__('navigator_node')
        self.subscription = self.create_subscription(String, 'next_room', self.callback, 10)
        self.navigator = BasicNavigator()
        self.navigator.waitUntilNav2Active()
        self.get_logger().info('Navigator Node Started - Nav2 Active')
        self.room_locations = {
            'kitchen': (2.0, 3.0, 0.0),
            'bathroom': (4.0, 1.0, 0.0),
            'bedroom': (6.0, 2.0, 0.0),
            'living_room': (3.0, 5.0, 0.0)
        }

    def callback(self, msg):
        room = msg.data
        if room in self.room_locations:
            pose = PoseStamped()
            pose.header.frame_id = 'map'
            pose.header.stamp = self.get_clock().now().to_msg()
            pose.pose.position.x = self.room_locations[room][0]
            pose.pose.position.y = self.room_locations[room][1]
            pose.pose.orientation.w = 1.0

            self.navigator.goToPose(pose)
            self.get_logger().info(f'Navigating to: {room}')
        else:
            self.get_logger().warn(f'Room {room} not found in map!')


def main(args=None):
    rclpy.init(args=args)
    node = InputNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
