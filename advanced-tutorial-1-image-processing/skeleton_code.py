from tkinter import Tk

import cv2
import numpy as np


# You should have no reason to modify this class
class UnitDisplayWindow:
    def __init__(
        self,
        group_name="Group name here",
        window_name="displayWindow1",
        window_height=Tk().winfo_screenheight(),
        window_width=Tk().winfo_screenwidth(),
    ):
        self.group_name = group_name
        self.window_name = window_name

        self.title_height = 100
        self.window_height = window_height - self.title_height
        self.window_width = window_width

        self.window = np.zeros((window_height, window_width, 3), dtype=np.uint8)

        self.unit_detection_count = 4
        self.unit_box_width = int(self.window_width / self.unit_detection_count)
        self.unit_box_height = self.window_height

        self.font = cv2.FONT_HERSHEY_SIMPLEX
        self.font_scale = 2
        self.font_thickness = 5

    # helper function to draw 1 of the 4 squares
    def draw_shape(self, unit, x, y):
        # Draw the background color
        background_top_left = (x, y)
        background_bottom_right = (x + self.unit_box_width, y + self.unit_box_height)
        cv2.rectangle(
            self.window,
            background_top_left,
            background_bottom_right,
            (200, 200, 200),
            -1,
            cv2.LINE_AA,
        )

        # Draw the black border of square
        black_border_top_left = (
            x,
            y + self.unit_box_height // 3 * 2 - self.unit_box_width // 2,
        )
        black_border_bottom_right = (
            x + self.unit_box_width,
            y + self.unit_box_height // 3 * 2 + self.unit_box_width // 2,
        )
        cv2.rectangle(
            self.window,
            black_border_top_left,
            black_border_bottom_right,
            (0, 0, 0),
            -1,
            cv2.LINE_AA,
        )
        # Draw the inner of the square
        inner_square_top_left = (
            x + self.unit_box_width // 20,
            y + self.unit_box_height // 3 * 2 - self.unit_box_width * 9 // 20,
        )
        inner_square_bottom_right = (
            x + self.unit_box_width * 19 // 20,
            y + self.unit_box_height // 3 * 2 + self.unit_box_width * 9 // 20,
        )
        cv2.rectangle(
            self.window,
            inner_square_top_left,
            inner_square_bottom_right,
            (200, 200, 200),
            -1,
            cv2.LINE_AA,
        )

        if unit == "Conducting Unit":
            # Draw Square Conducting Unit
            square_size = self.unit_box_width // 3 * 2
            cv2.rectangle(
                self.window,
                (
                    x + self.unit_box_width // 2 - square_size // 2,
                    y + self.unit_box_height // 3 * 2 - square_size // 2,
                ),
                (
                    x + self.unit_box_width // 2 + square_size // 2,
                    y + self.unit_box_height // 3 * 2 + square_size // 2,
                ),
                (255, 0, 0),
                -1,
            )
        elif unit == "Signal Unit":
            # Draw Circle Signal Unit
            circle_radius = self.unit_box_width // 4
            cv2.circle(
                self.window,
                (x + self.unit_box_width // 2, y + self.unit_box_height // 3 * 2),
                circle_radius,
                (0, 0, 255),
                -1,
            )
        # For "Empty", we do nothing (the box remains empty)

    # helper function to draw the 4 squares
    def display(self, __unit_detection_list):
        # add a white title bar
        self.window[self.window_height :, :] = (255, 255, 255)

        # add the title "RDC 2024 Unit Detection"
        title = "RDC 2024 Unit Detection : " + self.group_name
        title_size = cv2.getTextSize(
            title, self.font, self.font_scale, self.font_thickness
        )[0]
        title_x = (self.window_width - title_size[0]) // 2
        title_y = self.window_height + ((self.title_height + title_size[1]) // 2)
        cv2.putText(
            self.window,
            title,
            (title_x, title_y),
            self.font,
            self.font_scale,
            (0, 0, 0),
            self.font_thickness,
            cv2.LINE_AA,
        )

        # for the 4 squares
        for i in range(self.unit_detection_count):
            unit = __unit_detection_list[i]
            self.draw_shape(unit, i * self.unit_box_width, 0)

            # prepare the number at the center of each color box
            number = str(i + 1)
            text_size = cv2.getTextSize(
                number, self.font, self.font_scale, self.font_thickness
            )[0]
            text_x = (i * self.unit_box_width) + (
                (self.unit_box_width - text_size[0]) // 2
            )
            text_y = (self.unit_box_height + text_size[1]) // 3

            # Draw a black square beneath the number
            square_size = text_size[1] + 40  # Add some padding
            square_top_left = (
                text_x - int(0.5 * (square_size // 2)),
                text_y - 3 * (text_size[1] // 2),
            )
            square_bottom_right = (
                text_x + int(1.5 * (square_size // 2)),
                text_y + (text_size[1] // 2),
            )
            cv2.rectangle(
                self.window,
                square_top_left,
                square_bottom_right,
                (0, 0, 0),
                -1,
                cv2.LINE_AA,
            )

            # Draw the number
            cv2.putText(
                self.window,
                number,
                (text_x, text_y),
                self.font,
                self.font_scale,
                (255, 255, 255),
                self.font_thickness,
                cv2.LINE_AA,
            )

        cv2.namedWindow(self.window_name, cv2.WND_PROP_FULLSCREEN)
        cv2.setWindowProperty(
            self.window_name, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN
        )
        cv2.imshow(self.window_name, self.window)


if __name__ == "__main__":
    # TODO: Change your team's name
    unit_display = UnitDisplayWindow(
        group_name="RDC Team 0",
    )

    unit_detection_list = ["Empty", "Empty", "Empty", "Empty"]

    while True:
        # TODO: Change the detection values here based on your detection result
        unit_detection_list[0] = "Empty"
        unit_detection_list[1] = "Conducting Unit"
        unit_detection_list[2] = "Signal Unit"
        unit_detection_list[3] = "Empty"

        # Updates display
        unit_display.display(unit_detection_list)

        if cv2.waitKey(10) & 0xFF == ord("q"):  # waits for 'q' key to be pressed
            break

    cv2.destroyAllWindows()
