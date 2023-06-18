#ifndef SANDBOX_SRC_MAIN_STATE_H_
#define SANDBOX_SRC_MAIN_STATE_H_

/**
 * @file main_state.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Main state of the sandbox application.
 * @copyright Copyright (c) 2022 - 2023
 */

// NOTE: The main state is currently only for testing purposes.
class MainState
{
public:
    MainState();

    void Update();
    void Render();

private:
    size_t test_unit;
    size_t theme_unit;

    void CheckIsPressed(std::string item_id);
    void CheckIsHovered(std::string item_id);
};

#endif  // SANDBOX_SRC_MAIN_STATE_H_
