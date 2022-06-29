Preferences preferences;

void UploadRun(String run) {
  preferences.putString("run", run);
}

String ReadRun() {
  return preferences.getString("run", "");
}

void ShowRun() {
  Serial.print(ReadRun());
}
