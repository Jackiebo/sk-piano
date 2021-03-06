#include "LightStrip.h"
#include "LightStripVisualizer.h"

class LifeVisualizer : public LightStripVisualizer {
  public:
    LifeVisualizer(LightStrip& strip);
    ~LifeVisualizer();

    virtual void onKeyDown(Key key);
    virtual void onKeyUp(Key key);
    virtual void onPassFinished(bool something_changed);
    virtual void reset();

  private:
    int pixelForKey(Key key);

    Color* pixels;
    Color* old_pixels;
};
