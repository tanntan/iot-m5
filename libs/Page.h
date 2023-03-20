#ifndef LTLABS_UI_PAGE
#define LTLABS_UI_PAGE

#include <M5Stack.h>

using namespace std;

namespace LTLabs::Page {
  class Page {
    Page* nextPage;
    Page* previousPage;

    public:
      // virtual void draw(boolean &isFirstRun);
  };
}

#endif
