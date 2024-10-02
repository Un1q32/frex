char *strerror(int errnum) {
  switch (errnum) {
  case 0:
    return "No error";
  default:
    return "Unknown error";
  }
}
