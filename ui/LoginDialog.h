// generated by Fast Light User Interface Designer (fluid) version 1.0110

#ifndef LoginDialog_h
#define LoginDialog_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <stdio.h>
#include <stdlib.h>
#include "../client_prot.h"
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include "../connection.h"
#include <FL/Fl_Button.H>
#include "HelpDialog.h"
#include "Credits.h"
#include <FL/Fl_Return_Button.H>
#include "OptionsDialog.h"
#include "../Options.h"

class LoginDialog {
public:
  Fl_Window* Init(const char *email, const char *license, bool allowTest);
  Fl_Window *fWindow;
private:
  Fl_Input *fEmail;
  Fl_Input *fPassword;
  Fl_Input *fLicenseKey;
public:
  Fl_Output *fVersion;
  Fl_Output *fProtocol;
  Fl_Output *fMessage;
private:
  void cb_Test_i(Fl_Button*, void*);
  static void cb_Test(Fl_Button*, void*);
  void cb_Help_i(Fl_Button*, void*);
  static void cb_Help(Fl_Button*, void*);
  void cb_Credits_i(Fl_Button*, void*);
  static void cb_Credits(Fl_Button*, void*);
  void cb_Ok_i(Fl_Return_Button*, void*);
  static void cb_Ok(Fl_Return_Button*, void*);
  void cb_Cancel_i(Fl_Button*, void*);
  static void cb_Cancel(Fl_Button*, void*);
  void cb_Options_i(Fl_Button*, void*);
  static void cb_Options(Fl_Button*, void*);
public:
  void show(int vMajor, int vMinor);
  const char * Email() const;
  const char * Password() const;
  const char * LicenseKey() const;
  LoginDialog();
  ~LoginDialog();
  bool fTesting; // Use a login with test name, no password
  bool fFullLogin; 
};
#endif
