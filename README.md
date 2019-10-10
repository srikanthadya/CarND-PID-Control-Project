# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
## PID Controller

In an earlier project we had implemented a behavioral cloning algorithm in Python which would look at the image of the track ahead and predict what the steering angle should be to maintain the lane and drive around the simulator track. 

Another way to drive around the track would be to use the PID controller. The task of a PID controller is to ensure the vehicle is in the center of the lane by correcting for the error caused by deviating from the lane center. This deviation from the lane center is termed as **Cross Track Error (CTE)**. 

This correction **(Steering Angle)** is composed of three terms, the Proportional term, Integral Term and the Diffrential term and is expressed as below.


<a href="https://www.codecogs.com/eqnedit.php?latex=Steering&space;Angle&space;=&space;K_{p}*CTE&space;&plus;&space;K_{d}*\frac{d&space;(CTE)}{dt}&plus;&space;K_{i}*\int(CTE\&space;dt)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?Steering&space;Angle&space;=&space;K_{p}*CTE&space;&plus;&space;K_{d}*\frac{d&space;(CTE)}{dt}&plus;&space;K_{i}*\int(CTE\&space;dt)" title="Steering Angle = K_{p}*CTE + K_{d}*\frac{d (CTE)}{dt}+ K_{i}*\int(CTE\ dt)" /></a>


## Proportional term

The proportional term tries to make to CTE reduce to zero by steering towards the center line. This term has the largest contribution toward the steering correction. But if used alone, this term will cause the vehicle to oscillate about the centerline. The best way to come up with an initial guess for the proportional constant Kp is to set the other two to zero and increase Kp untill the vehicle oscillates about the center line. 

## Diffrential term

In order to reduce the vehicle's oscillation explained above, the diffrential term is introduced such that the steering correction reduces as the CTE gets closer to zero. This ensures that as the vehicle nears the centerline, the steering correction also reduces proportionally this preventing an overshoot. 

## Integral term

A vehicle might have an inherent bias like a steering drift which will prevent it from achievng a zero CTE. To counter this, the CTE is accumulated and a correction proportional to the accumulated error is added.

![PID_image](twiddle.png)

## Tuning the PID coefficients

As mentioned above the initial values of Kp, Kd and Ki can be obtained manually. Initially Kd an Ki are set to zero and Kp is increased untill the vehicle starts oscillating about the center line. Once this is achieved, Kd is increased untill the oscillations reduce and the vehicle follows the centerline. Ki on this track did not have much of an influence has been set to a very low value. 

## Twiddle

Once we have an initial value for the three parameters, we allow the twiddle algorithm to fine tune the coefficients further. It was noticed that the coefficients oscillated aboout the initial value and finally converged to the same values as the initial value. 

## Video

[Video link](https://youtu.be/mxTvz2GgP0Q)
_____________________________________________________________________________________________________________________________________________________________________________
## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

