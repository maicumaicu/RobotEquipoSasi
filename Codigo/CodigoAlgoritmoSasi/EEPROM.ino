Preferences preferences;

void UploadRun(String Address, String run){
  preferences.putString("run", run);
}

String ReadRun(String Address){
  return preferences.getString(Address, "");
}
