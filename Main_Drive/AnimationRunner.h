// ====================================================================================================================
// This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License. To view a
// copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or send a letter to
// Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
// ====================================================================================================================

// ====================================================================================================================
//                         Joe's Drive Powered by Naigon
//                         19 June 2020
//                         Scott DeBoer
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This is part of the add-on library for Joe's Drive created by Naigon.
// ====================================================================================================================

#ifndef __NaigonBB8_AnimationRunner_h_
#define __NaigonBB8_AnimationRunner_h_

#include "Arduino.h"

namespace NaigonBB8
{

// Forward declarations for Animation classes.
class AnimationState;
enum AnimationTarget : uint8_t;
struct IAnimation;

///////////////////////////////////////////////////////////////////////////////////////
// @summary Class that is responsible for managing and running all the specified
//          animations for the system. It will be used to randomly select an animation
//          depending on the passed in AnimationTarget, and is responsible for passing
//          the AnimationState at each iteration up to the main program.
//
//          Note that for simplicity this is just a normal class but it is expected to
//          act like a singleton for the system, and thus only one of these should be
//          created at the top .ino file.
///////////////////////////////////////////////////////////////////////////////////////
class AnimationRunner
{
public:
    ///////////////////////////////////////////////////////////////////////////////////
    // @summary Constructs an instance of the AnimationRunner class.
    //
    // @param   numAnimations
    //          Total number of animations known by the system. The animations array
    //          needs to be less than or equal to this size.
    //
    // @param   animations
    //          Array of pointers to all IAnimation instances the system knows about.
    ///////////////////////////////////////////////////////////////////////////////////
    AnimationRunner(int numAnimations, IAnimation *animations[]);

    ///////////////////////////////////////////////////////////////////////////////////
    // @summary Determins if there is an animation running or not.
    //
    // @ret     true if an animation is running; otherwise, false.
    ///////////////////////////////////////////////////////////////////////////////////
    bool IsRunning() const;

    ///////////////////////////////////////////////////////////////////////////////////
    // @summary Stops the currently running animation. No-op if nothing is running.
    ///////////////////////////////////////////////////////////////////////////////////
    void StopCurrentAnimation();

    ///////////////////////////////////////////////////////////////////////////////////
    // @summary Generates the appropriate AnimationState for this instance. This
    //          method should be called once per Arduino loop().
    //
    // @ret     Constant pointer to the AnimationState that should be run this
    //          iteration.
    ///////////////////////////////////////////////////////////////////////////////////
    const AnimationState* RunIteration();

    ///////////////////////////////////////////////////////////////////////////////////
    // @summary Start a randomly selected animation.
    //
    // @param   AnimationTarget which should be used for the random selection. Any
    //          animation selected must be of this type, or the Any type. If Any IsRunning
    //          passed in than any of the animations will be selected.
    ///////////////////////////////////////////////////////////////////////////////////
    void SelectAndStartAnimation(AnimationTarget aTarget);

private:
    int _numBank1, _numBank2, _numBank3, _numBank4, _numAnimations;
    IAnimation* _currentAnimation;
    IAnimation **_animations;
};

}   //namespace NaigonBB8

#endif  //__NaigonBB8_AnimationRunner_h_
