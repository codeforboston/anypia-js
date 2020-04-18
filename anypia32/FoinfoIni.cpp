// @doc FOINFOINI
// $Id: FoinfoIni.cpp 1.4.1.1 2012/03/08 06:55:06EST 277133 Development 277133(2012/03/08 06:55:47EST) $
// @module FoinfoIni.cpp |
//
// Functions to handle field office information in an ini file.

#include "stdafx.h"
#include "FoinfoIni.h"

const char *FieldOfficeInfoIni::section = "Field Office Info";
const char *FieldOfficeInfoIni::name = "Name";
const char *FieldOfficeInfoIni::title = "Title";
const char *FieldOfficeInfoIni::address1 = "Address1";
const char *FieldOfficeInfoIni::address2 = "Address2";
const char *FieldOfficeInfoIni::address3 = "Address3";
const char *FieldOfficeInfoIni::address4 = "Address4";

// @mfunc Initializes field office info.

FieldOfficeInfoIni::FieldOfficeInfoIni() : FieldOfficeInfo()
{ }

// @mfunc Reads field office info from ini file.

void FieldOfficeInfoIni::read()
{
  setFieldOfficeName(
    AfxGetApp()->GetProfileString(section, name, "").GetString());
  setFieldOfficeTitle(
    AfxGetApp()->GetProfileString(section, title, "").GetString());
  setAddress(0,
    AfxGetApp()->GetProfileString(section, address1, "").GetString());
  setAddress(1,
    AfxGetApp()->GetProfileString(section, address2, "").GetString());
  setAddress(2,
    AfxGetApp()->GetProfileString(section, address3, "").GetString());
  setAddress(3,
    AfxGetApp()->GetProfileString(section, address4, "").GetString());
}

// @mfunc Saves field office info to ini file.

void FieldOfficeInfoIni::write()
{
  if (savename) {
    AfxGetApp()->WriteProfileString(section, name,
      getFieldOfficeName().c_str());
  }
  if (savetitle) {
    AfxGetApp()->WriteProfileString(section, title,
      getFieldOfficeTitle().c_str());
  }
  if (saveaddress1) {
    AfxGetApp()->WriteProfileString(section, address1, getAddress(0).c_str());
  }
  if (saveaddress2) {
    AfxGetApp()->WriteProfileString(section, address2, getAddress(1).c_str());
  }
  if (saveaddress3) {
    AfxGetApp()->WriteProfileString(section, address3, getAddress(2).c_str());
  }
  if (saveaddress4) {
    AfxGetApp()->WriteProfileString(section, address4, getAddress(3).c_str());
  }
}

// @mfunc Dummy function for ini version.

void FieldOfficeInfoIni::setData()
{ }
