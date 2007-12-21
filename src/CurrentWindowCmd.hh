// CurrentWindowCmd.hh for Fluxbox - an X11 Window manager
// Copyright (c) 2003 - 2006 Henrik Kinnunen (fluxgen at fluxbox dot org)
//                and Simon Bowden (rathnor at users.sourceforge.net)
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// $Id$

#ifndef CURRENTWINDOWCMD_HH
#define CURRENTWINDOWCMD_HH

#include "Command.hh"
#include "Window.hh"
#include "ClientPattern.hh"

/// helper class for window commands
/// calls real_execute if there's a focused window or a window in button press/release window
class WindowHelperCmd: public FbTk::Command {
public:
    explicit WindowHelperCmd() { }

    void execute();

protected:
    FluxboxWindow &fbwindow();
    virtual void real_execute() = 0;
};

class WindowHelperBoolCmd: public FbTk::BoolCommand {
public:
    explicit WindowHelperBoolCmd() { }

    bool bool_execute();

protected:
    FluxboxWindow &fbwindow();
    WinClient &winclient();
    virtual bool real_execute() = 0;
};

/// command that calls FluxboxWindow::<the function> on execute()
/// similar to FbTk::SimpleCommand<T>
class CurrentWindowCmd: public WindowHelperCmd {
public:
    typedef void (FluxboxWindow::* Action)();
    explicit CurrentWindowCmd(Action action): m_action(action) { }
    void real_execute();
private:
    Action m_action;
};

class SetHeadCmd : public WindowHelperCmd {
public:
    explicit SetHeadCmd(int head) : m_head(head) { }
protected:
    void real_execute();
private:
    const int m_head;
};

class SendToWorkspaceCmd: public WindowHelperCmd {
public:
    explicit SendToWorkspaceCmd(int workspace_num):m_workspace_num(workspace_num) { }
protected:
    void real_execute();
private:
    const int m_workspace_num;
};

class SendToNextWorkspaceCmd: public WindowHelperCmd {
public:
    explicit SendToNextWorkspaceCmd(int delta):m_delta(delta) { }
protected:
    void real_execute();
private:
    const int m_delta;
};

class SendToPrevWorkspaceCmd: public WindowHelperCmd {
public:
    explicit SendToPrevWorkspaceCmd(int delta):m_delta(delta) { }
protected:
    void real_execute();
private:
    const int m_delta;
};

class TakeToWorkspaceCmd : public WindowHelperCmd {
public:
    explicit TakeToWorkspaceCmd(int workspace_num) : m_workspace_num(workspace_num) { }
protected:
    void real_execute();
private:
    const int m_workspace_num;
};

class TakeToNextWorkspaceCmd : public WindowHelperCmd {
public:
    explicit TakeToNextWorkspaceCmd(int delta) : m_delta(delta) { }
protected:
    void real_execute();
private:
    const int m_delta;
};

class TakeToPrevWorkspaceCmd : public WindowHelperCmd {
public:
    explicit TakeToPrevWorkspaceCmd(int delta) : m_delta(delta) { }
protected:
    void real_execute();
private:
    const int m_delta;
};


// goto tab
class GoToTabCmd: public WindowHelperCmd {
public:
    explicit GoToTabCmd(int tab_num):m_tab_num(tab_num) { }
protected:
    void real_execute();
private:
    const int m_tab_num;
};

// begin moving with mouse
class StartMovingCmd: public WindowHelperCmd {
public:
    StartMovingCmd() { }
protected:
    void real_execute();
};

// begin resizing with mouse
class StartResizingCmd: public WindowHelperCmd {
public:
    explicit StartResizingCmd(FluxboxWindow::ResizeModel mode):m_mode(mode) { }
    static FbTk::Command *parse(const std::string &command,
                                const std::string &args, bool trusted);
protected:
    void real_execute();
private:
    const FluxboxWindow::ResizeModel m_mode;
};

// begin tabbing with mouse
class StartTabbingCmd: public WindowHelperCmd {
public:
    StartTabbingCmd() { }
protected:
    void real_execute();
};

// move cmd, relative position
class MoveCmd: public WindowHelperCmd {
public:
    explicit MoveCmd(const int step_size_x, const int step_size_y);
    static FbTk::Command *parse(const std::string &command,
                                const std::string &args, bool trusted);
protected:
    void real_execute();

private:
    const int m_step_size_x;
    const int m_step_size_y;
};

// resize cmd, relative size
class ResizeCmd: public WindowHelperCmd{
public:
  explicit ResizeCmd(int step_size_x, int step_size_y);
    static FbTk::Command *parse(const std::string &command,
                                const std::string &args, bool trusted);
protected:
  void real_execute();

private:

  const int m_step_size_x;
  const int m_step_size_y;
};

class MoveToCmd: public WindowHelperCmd {
public:
    enum {
        LEFT =  1 << 0,
        RIGHT = 1 << 1,
        UPPER = 1 << 2,
        LOWER = 1 << 3,

        IGNORE_X = 1 << 8,
        IGNORE_Y = 1 << 9
    };
    explicit MoveToCmd(const int step_size_x, const int step_size_y, const unsigned int refc);
    static FbTk::Command *parse(const std::string &command,
                                const std::string &args, bool trusted);
protected:
    void real_execute();

private:
    const int m_step_size_x;
    const int m_step_size_y;
    const unsigned int m_refc;
};

// resize cmd
class ResizeToCmd: public WindowHelperCmd{
public:
    explicit ResizeToCmd(int step_size_x, int step_size_y);
protected:
    void real_execute();
private:
    const int m_step_size_x;
    const int m_step_size_y;
};

class FullscreenCmd: public WindowHelperCmd{
public:
    explicit FullscreenCmd();
protected:
    void real_execute();
};

class SetAlphaCmd: public WindowHelperCmd {
public:
    SetAlphaCmd(int focus, bool rel, int unfocus, bool unrel);
    static FbTk::Command *parse(const std::string &command,
                                const std::string &args, bool trusted);
protected:
    void real_execute();
private:
    int m_focus, m_unfocus;
    int m_relative, m_un_relative;
};

class MatchCmd: public WindowHelperBoolCmd {
public:
    MatchCmd(const std::string &pat): m_pat(pat.c_str()) { };
protected:
    bool real_execute();
private:
    ClientPattern m_pat;
};

#endif // CURRENTWINDOWCMD_HH
