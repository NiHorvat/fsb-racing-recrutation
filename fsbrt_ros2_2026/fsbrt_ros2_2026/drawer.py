import matplotlib.pyplot as plt
from multiprocessing import Process, Queue
import math
import os
from pathlib import Path
from datetime import datetime
import matplotlib.animation as animation
import pickle

import rclpy
from rclpy.logging import get_logger

from fsbrt_ros2_2026 import world as wr
from fsbrt_ros2_2026 import settings

"""
Author: Matej Lovreković & Luka Bradarić-Lisić

FSBRT Autonomous - Recruitment task

Opens a thread that plots live current position of a car. Also contains a functions for plotting and saving graphs.
"""

ARROW_LENGTH = 1.5 #m
ARROW_HEAD_WIDTH = 1 #m

_logger = get_logger("drawer")

#Store paths where drawing will be saved.
#When installed, the package dir is read-only, so default to the user's home
#(overridable via the FSBRT_DRAWINGS_DIR environment variable).
_drawings_root = os.environ.get(
    "FSBRT_DRAWINGS_DIR",
    os.path.join(os.path.expanduser("~"), "fsbrt_ros2_2026_drawings"))
vel_dir_path = os.path.join(_drawings_root, "velocity")
ang_vel_dir_path = os.path.join(_drawings_root, "angular_velocity")
os.makedirs(vel_dir_path, exist_ok=True)
os.makedirs(ang_vel_dir_path, exist_ok=True)

# Queue that is used to send data to the drawer process
arrow_queue = Queue()

def plt_draw_arrows(x, y, theta):
    """
    Function that queues the point for it to be drawn on the GUI.
    """

    arrow_queue.put((x,y, theta))

def save_figure_to_file(fig, path):
    """
    Function that saves figure to a raw byte file (pickle file). File can be later loaded with the "redraw_figure.py" script.
    """

    pickle.dump(fig, open(path, "wb"))

def end_result_speed(command_speed, speed, sampling):
    """
    Function that saves speed with respect to time thoughout whole run.
    """

    # Plotting
    fig3, ax3 = plt.subplots()

    time_steps = [i*settings.X_SECONDS_APPEREANCE for i in range(len(command_speed))]

    ax3.plot(time_steps, command_speed, label='User requested velocity')
    ax3.plot(time_steps, speed, label='Actual velocity')
    ax3.set_xlabel('t [s]')
    ax3.set_ylabel('v [m/s]')
    ax3.set_title('Velocity review')
    ax3.grid(True)
    fig3.legend()

    save_figure_to_file(fig3, vel_dir_path+'/Velocity_'+str(datetime.now())+'.matfig')
    _logger.info('Saving speed')


def end_result_steering(ang_command_vel, ang_vel, sampling):
    """
    Function that saves angular velocity with respect to time thoughout whole run.
    """

    # Plotting
    time_steps = [i*settings.X_SECONDS_APPEREANCE for i in range(len(ang_command_vel))]
    ang_command_vel_deg = [i*(180/math.pi) for i in ang_command_vel]
    ang_vel_deg = [i*(180/math.pi) for i in ang_vel]

    fig2, ax2 = plt.subplots()
    ax2.plot(time_steps, ang_command_vel_deg, label='User requested angular velocity (yaw rate)')
    ax2.plot(time_steps, ang_vel_deg, label='Actual angular velocity (yaw rate)')
    ax2.set_xlabel('t [s]')
    ax2.set_ylabel('w [deg/s]')
    ax2.set_title('Angular velocity review')
    ax2.grid(True)
    fig2.legend()

    save_figure_to_file(fig2, ang_vel_dir_path+'/Angular_velocity_'+str(datetime.now())+'.matfig')
    _logger.info('Saving steering')


def drawing_process(queue):
    """
    Internal process function that handles draw requests from queue.
    """



    def draw_frame(frame_id):

        """
        Inside function that draws frame on matplotlib animation object callback.
        """

        while not queue.empty():

            x,y,theta = queue.get()
            dx, dy = ARROW_LENGTH*math.cos(theta), ARROW_LENGTH*math.sin(theta)

            #Clear recent plot and draw it again
            ax1.cla()
            fig1.subplots_adjust(left=0, right=1, top=1, bottom=0)
            ax1.set_xlim(0,300)
            ax1.set_ylim(0,300)
            fig1.suptitle('Cheap drone view')
            x_o, y_o = zip(*wr.outer_points)
            x_i, y_i = zip(*wr.inner_points)
            ax1.scatter(x_o, y_o, marker='^',color='b', s=2)
            ax1.scatter(x_i, y_i, marker='^',color='y', s=2)

            ax1.arrow(x, y, dx, dy, head_width=ARROW_HEAD_WIDTH, color='k') #current formula position


    fig1, ax1 = plt.subplots(figsize=(9,9))
    anim = animation.FuncAnimation(fig1, draw_frame, interval=settings.X_SECONDS_APPEREANCE*1000)
    plt.show()



def init_drawer():
    """
    Function that initialises the drawer handler.
    """


    drawer_handle = Process(target=drawing_process,daemon=True,args=(arrow_queue,))
    drawer_handle.start()
