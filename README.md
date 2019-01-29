# Self-Driving Experiments

## Why?

Everyone else seems to be working on self-driving vehicles at the moment, so I wanted to get in on the fun.

## Is the construction, etc documented anywhere?

Yes.  You can follow the progress, and even offer comments and suggestions at

https://blog.nowwhywouldyoudothat.com/2018/02/diy-self-driving.html

## What is your car?

I am using a kid's ride-on electric car as a platform because I already have it.  This means I have to rework the steering mechanism (which is woefully simple) but that is just one more obstacle to solve.

The car itself uses a six-volt battery and electric motor to drive a single rear wheel.  While this doesn't sound impressive, with nobody on-board, the performance and battery life should be quite acceptable.  Also, it's big and looks like a proper car.

## What is the compute platform?

There are two compute modules in the car at present:

### Main CPU

This was originally a Raspberry Pi 3B+, but the comparitively low memory made it difficult to support both navigation and vision on one machine.  More recently I have changed to a FriendlyArm NanoPC-T4, it runs Ubuntu in place of Raspbian, but the code is pretty much compatible between the two.

### Motion Control
This is an Arduino Uno or similar which accepts commands from the Main CPU over a serial connection and controls the motor and steering systems.

Using this method allows me to free the main CPU from effectively real-time control tasks, as well as abstracting vehicle control from the navigation and detection routines.  The platform has now been tested on both the original car and a tracked platform.

In terms of the electronic interfaces for motors and the like, I will be making every effort to use off-the-shelf components.

## Is this a fork of someone else's project?

No.  I realise lots of people have done great stuff already, but I learn more by making my own mistakes.

Of course if it all falls in a heap, I reserve the right to remove the above statement...

## Can I help?

Yes of course.  The more the merrier.

## Can you tell me how to adapt a brand X ride-on car to your software?

Umm... I doubt it.  I will have enough trouble with my own, but I intend to document my progress, so hopefully that will help you.

## Can this software be used to control a *real* car?

You would need to rework the motor control routines to interface with whatever you have, but it is something I intend to work on soon.

## Can this software control a UAV (drone) or a boat?

There is no position or altimetry in the code at present, so it won't control an aircraft.  Anyway, there are lots of good flight controller projects out there already.

As for a boat, because the vision software looks for edges, while it would control the boat I don't think the steering control is going to work well.

## Should I put my son/daughter/pet/spouse into the car when it's done?

Are you serious?  While I can't actually *stop* you doing that, I strongly advise against doing so!
