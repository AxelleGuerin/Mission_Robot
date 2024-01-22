// copilot.h

#ifndef COPILOT_H
#define COPILOT_H

#include "pilot.h"

/**
 * @file copilot.h
 * @brief Declaration of the Copilot class.
 * @license MIT
 */

/**
 * @brief Initiates a path for the robot to follow.
 */
extern void copilot_start_path(void);

/**
 * @brief Moves the robot to the next step in the path.
 */
extern void copilot_next_step(void);

/**
 * @brief Stops the robot when the current step in the path is completed.
 *
 * @return The status of stopping at the step completion.
 */
extern move_status copilot_stop_at_step_completion(void);

/**
 * @brief Checks if the entire path is completed.
 *
 * @return True if the path is completed, otherwise false.
 */
extern int copilot_is_path_completed(void);

/**
 * @brief Destroys the current path.
 * @return EXIT_SUCCESS if the path is destroyed, otherwise EXIT_FAILURE.
 */
extern int copilot_destroy_path(void);

/**
 * @brief Adds a step to the path at a specific index.
 *
 * @param index The index at which to add the step.
 * @param type The type of step to be added to the path.
 * @param value the distance or degree of the move
 * @return EXIT_SUCCESS if the step is added successfully, otherwise
 * EXIT_FAILURE.
 */
extern int copilot_add_step(int index, move step);

/**
 * @brief get the step at a specific index.
 *
 * @param index The index at which to get the step
 * @return return the move of the indexed step or Zero move if index exceed path
 * limits
 */
extern move copilot_get_step(int index);

/**
 * @brief allocate memory for a new path.
 *
 * @param steps_nb number of steps of the new path
 * @return return EXIT_SUCCESS if the path is created successfully, otherwise
 * EXIT_FAILURE.
 */
extern int copilot_create_path(int steps_nb);

/**
 * @brief get the number of steps of the current path.
 *
 * @return return the number of steps of the path
 */
extern int copilot_get_number_steps_in_path();

#endif // COPILOT_H
