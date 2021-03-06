/*
// Author: Josias Alexandre Oliveira
//
// Based on the Matt Bradley's Masters Degree thesis and work
// Copyright (c) 2012 Matt Bradley
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef STANLEY_METHOD_CONTROLLER_HPP
#define STANLEY_METHOD_CONTROLLER_HPP

#include "../Entities/State2D.hpp"
#include "../VehicleModel/VehicleModel.hpp"
#include "../GridMap/InternalGridMap.hpp"

namespace astar {

enum ControllerState {CSStandby, CSStopped, CSForwardDrive, CSReverseDrive, CSComplete};

class StanleyController {

    private:

        const astar::InternalGridMapRef grid;

        // the vehicle model
        const astar::VehicleModel &vehicle_model;

        // the robot state
        State2D car;

        // the controller state
        astar::ControllerState cs = CSStandby;

        // the way point index
        unsigned int next_waypoint;
        unsigned int prev_waypoint;

        // the resolution time to build the command list
        double dt;

        // reverse mode flag
        bool reverse_mode;

        // the fake front axle position
        Pose2D front_axle, fake_front_axle;

        // the closest point
        Pose2D closest_point;

        // left and right vectors
        Vector2D<double> left, right;

        // the input path
        std::vector<astar::State2D> raw_path;

        // the current forward path
        std::vector<astar::State2D> forward_path;

        // the current reverse path
        std::vector<astar::State2D> reverse_path;

        // the consolidated path flag
        bool consolidated_path;

        // the raw path size
        unsigned int raw_path_size;

        // the raw path last index
        int raw_path_last_index;

        // the stopping points vector
        std::vector<unsigned int> stopping;

        // double the past phi error
        double prev_wheel_angle_error;

        // the velocity past error
        double vpasterror;

        // the last cusp
        unsigned int last_cusp;

         // set the appropriated low speeds around the stopping points
        void UpdateLowSpeedRegions();

        // get the desired command given two states
        // the first and the last states remains the same
        bool ConsolidateStateList(astar::StateArrayPtr);

        // how far the car has moved between two points in the path
        double HowFarAlong(const astar::Pose2D &, const astar::Pose2D&, const astar::Pose2D&);

        // find the previous and next index in the path
        void Localize(const astar::State2D&, unsigned int&, unsigned int&);

        // find the closest point next to the front axle, fake or not
        Pose2D FindClosestPoint(const astar::State2D&, const astar::State2D&, const astar::State2D&);

        // the stopping point action
        astar::State2D Stopped(const astar::State2D&);

        // travel along the path - forward
        astar::State2D ForwardDrive(const astar::State2D&);

        // travel along the path - forward
        astar::State2D ReverseDrive(const astar::State2D&);

        void ShowPath(astar::StateArrayPtr);

    public:

        // basic constructor
        StanleyController(const astar::InternalGridMapRef grid_map, const astar::VehicleModel&);

        // get a Command list to follow a given path
        StateArrayPtr BuildAndFollowPath(astar::StateArrayPtr);

        // follow a given path
        StateArrayPtr FollowPath(const astar::State2D&);

        // the controller has a valid plan?
        bool HasValidPath(const astar::State2D&);

        // path following simulation
        StateArrayPtr FollowPathSimulation(astar::StateArrayPtr);

        // consolidate the input path  and build a new command list
        StateArrayPtr RebuildCommandList(const astar::State2D&, astar::StateArrayPtr);

        // get the next command
        StateArrayPtr GetCommandList(const astar::State2D&);

        // verify if the robot is lost

};

}

#endif
