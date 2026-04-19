#ifndef ROMPATCH_H
#define ROMPATCH_H

#include <cstdint>
#include <cstddef>
#include <vector>

enum class KernalRomImage {
    JiffyDOS,
    Rev1Prototype,
    Rev2Old,
    Rev3New,
    SX64,
    Unknown,
    CreatedByThisApp
};

// Read-only ROM görünümü
struct RomView {
    const uint8_t* data;
    std::size_t    size;

    // std::vector'den implicit dönüşüm
    RomView(const std::vector<uint8_t>& v) : data(v.data()), size(v.size()) {}
    // Ham pointer + boyuttan
    RomView(const uint8_t* d, std::size_t s) : data(d), size(s) {}
};

KernalRomImage detectKernalRomImage(RomView romView);
bool           isJiffy(RomView romView);
uint8_t        getTextColor(RomView romView);
uint8_t        getBorderColor(RomView romView);
uint8_t        getBackgroundColor(RomView romView);
unsigned char colorIndexToPETSCII(int colorIndex);

void setTextBorderBackgroundColor(std::vector<uint8_t>& romVec,
                                  uint8_t textColor,
                                  uint8_t borderColor,
                                  uint8_t backgroundColor);

void setCreatedByThisApp(std::vector<uint8_t>& romVec);

bool patchBlock(std::vector<uint8_t>& romVec,
                std::size_t offset,
                const uint8_t* src,
                std::size_t length);

// JiffyDos Logo
bool setJiffyDosLogo(std::vector<uint8_t>& romVec);
void setJiffyDosLogoSettings(std::vector<uint8_t>& romVec,
                             bool hasC64Text,
                             unsigned char *rightText,
                             bool noblink);
// READY.
bool setReady(std::vector<uint8_t>& romVec);
bool setReady2(std::vector<uint8_t>& romVec);
// OK
bool setOk(std::vector<uint8_t>& romVec);
// Extended READY.
bool setExtendedReady(std::vector<uint8_t>& romVec);
void setExtendedReadyAdvancedSettings(std::vector<uint8_t>& romVec,
                                      const unsigned char *yourText,
                                      int bootTextIndex,
                                      bool hasCursorColor,
                                      int cursorColorIndex,
                                      bool noblink,
                                      bool beep
                                      );
// ATARI Style
bool setAtari(std::vector<uint8_t>& romVec);
// DOS Style
bool setDos(std::vector<uint8_t>& romVec, bool finalOK=false);
bool setCDos(std::vector<uint8_t>& romVec, bool finalOK=false);
// Fake RAM Test
bool setFakeRam(std::vector<uint8_t>& romVec);
// Commodore (64) Logo
bool setCommodoreLogo64(std::vector<uint8_t> &romVec, int colorIndex);
bool setCommodoreLogo(std::vector<uint8_t> &romVec, int colorIndex);
bool setCommodoreLogoMono(std::vector<uint8_t> &romVec);
bool setCommodoreLogo64Mono(std::vector<uint8_t> &romVec);
void setCommodoreLogoEnhanced(std::vector<uint8_t>& romVec,
                              int colorIndex,
                              int c1,
                              int c2,
                              int topColor,
                              unsigned char *topline,
                              int bottomColor,
                              unsigned char *bottomline);
void setCommodoreLogo64Enhanced(std::vector<uint8_t>& romVec,
                              int colorIndex,
                              int c1,
                              int c2,
                              int top64Color,
                              int bottom64Color,
                              int topColor,
                              unsigned char *topline,
                              int bottomColor,
                              unsigned char *bottomline);
// IBM Style
bool setIBMStyle(std::vector<uint8_t> &romVec, int colorIndex);
// C64 Rainbow Bars
bool setC64RainbowBars(std::vector<uint8_t> &romVec, int colorIndex);
// Floppy Diskette Logo
bool setFloppyDiskette(std::vector<uint8_t> &romVec, int colorIndex);
// Horizontal Color Bars
bool setHorizontalColorBars(std::vector<uint8_t> &romVec, int colorIndex, int c1, int c2, int c3);
// Ultimate
bool setUltimateMono(std::vector<uint8_t> &romVec, int colorIndex);
bool setUltimate(std::vector<uint8_t> &romVec, int colorIndex);
void setUltimateEnhanced(std::vector<uint8_t>& romVec,
                                int colorIndex,
                                int c1,
                                int c2,
                                int topColor,
                                int bottomColor,
                                int topLineColor,
                                unsigned char *topline,
                                int bottomLineColor,
                                unsigned char *bottomline);
// commodore text
void setCommodoreText(std::vector<uint8_t>& romVec,
                    int colorIndex,
                    int c1,
                    int c2);
void setCommodoreTextMono(std::vector<uint8_t>& romVec,
                      int colorIndex);
#endif // ROMPATCH_H
