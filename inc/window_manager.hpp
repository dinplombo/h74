#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

namespace araknoid {

class WindowManager {
public:
    virtual ~WindowManager() = default;

    virtual bool open() = 0;

protected:
    WindowManager() = default;
    WindowManager(WindowManager const& a_other) = default;
    WindowManager& operator=(WindowManager const& a_other) = default;
};

} //namespace araknoid

#endif // WINDOW_MANAGER_HPP
