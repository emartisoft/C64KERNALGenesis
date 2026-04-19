#ifndef MODULES_H
#define MODULES_H

#include <QList>
#include "carditem.h"

QList<CardItem> items = {
    {
        0x001,
        "just_colors",
        ":/res/pictures/preview/just_colors.gif",
        "Just Colors",
        "A KERNAL patch for the Commodore 64 that lets you change border, background, and text colors — and nothing else",
        "Just Colors is a lean, mean, no-frills module for the C64 ROM KERNAL. No fancy tricks, no memory hacks, no IRQ wizardry — just a clean way to swap your border, background, and text colors without touching anything else. If you've ever booted up a project and thought \"this blue-on-blue situation has got to go\" — this one's for you, compadre.",
        false
    },

    {
        0x002,
        "just_ready",
        ":/res/pictures/preview/just_ready.gif",
        "Just READY.",
        "A clean and elegant take on C64 minimalism—Just Ready captures the true spirit of simplicity while giving just enough customization to make it feel personal",
        "Just Ready is a minimalist KERNAL patch for the Commodore 64 that focuses on purity and control. It lets you customize the border, background, and text colors exactly to your taste—nothing more, nothing less.\n\nWhat makes it stand out is its clean startup experience. When the C64 boots, you’re greeted with a bare “READY.” prompt, free from distractions or extra messages. It feels closer to the raw essence of the machine—simple, direct, and nostalgic.\n\nFor retro enthusiasts who appreciate a stripped-down environment and a personal visual touch, Just Ready delivers a subtle but satisfying refinement of the classic C64 experience.",
        false
    },

    {
        0x003,
        "just_ok",
        ":/res/pictures/preview/just_ok.gif",
        "Just COMMODORE 64 — OK Only",
        "A simple C64 KERNAL patch that lets you customize colors and shows only \"COMMODORE 64\" and \"OK\" on boot",
        "A neat KERNAL patch for the Commodore 64 that keeps things simple. Customize your border, background, and text colors, and enjoy a clean boot screen showing just:\n\nCOMMODORE 64\nOK\n\nNo distractions, no extras—just classic C64 charm with a touch of personalization.",
        false
    },

    {
        0x004,
         "extended_ready",
         ":/res/pictures/preview/just_ready_enhanced.gif",
         "READY. (Enhanced)",
         "A clean and flexible KERNAL patch that enhances the C64 boot experience with customizable visuals, optional startup text, and subtle retro-style tweaks",
         "READY. (Enhanced) is a sleek C64 KERNAL patch for retro enthusiasts, letting you fully customize your screen’s border, background, and text colors. On boot, display a personalized 24-character message or skip it entirely, finish with READY. or OK, and enjoy a startup beep. Control cursor blinking and even set its color independently of text for that authentic, polished Commodore feel.",
         true,
         CardItem::AccessType::Locked,
         "https://c64kernal.com/modules"
    },

    {
        0x005,
        "atari",
        ":/res/pictures/preview/atari.gif",
        "ATARI Style",
        "A tasteful C64 KERNAL patch that blends Atari-style aesthetics with classic Commodore identity, highlighted by its blue startup screen, steady cursor, and the iconic dotted “READY.” prompt",
        "ATARI Style is a subtle yet nostalgic KERNAL patch for the Commodore 64 that channels the spirit of Atari 8-bit machines. While it doesn’t fully replicate Atari’s color palette, the cool blue-toned startup screen and the non-blinking cursor evoke a familiar retro atmosphere. Still, it proudly stays true to its C64 roots with the iconic “READY.” prompt—dot included—offering a charming blend of two classic worlds for vintage computing enthusiasts. For those who don’t know, Atari greets you with just READY (without a dot).",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x100,
        "jiffydoslogo",
        ":/res/pictures/preview/jiffydos.gif",
        "JiffyDOS Logo",
        "A clean and nostalgic enhancement that gives your JiffyDOS-powered C64 a customizable, personality-filled startup with a classic PETSCII touch",
        "JiffyDOS Logo is a tasteful KERNAL patch for the Commodore 64 that adds a nostalgic visual flair to your JiffyDOS setup. On boot, you’re greeted with a PETSCII-crafted JiffyDOS logo, bringing a classic demo-scene vibe to the startup screen. Colors for border, background, and text are fully customizable, letting you fine-tune the look to your liking. For an extra personal touch, you can place a “C64” label in the lower-left corner and a version tag like “V6.01” (or any 7-character text) in the lower-right. Cursor blinking can also be toggled, rounding out this subtle yet charming enhancement—perfect for retro enthusiasts who want JiffyDOS with a bit more personality.",
        true,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x300,
        "dos_ready",
        ":/res/pictures/preview/dosru.gif",
        "PC DOS Style - READY. (UPPERCASE)",
        "A stylish and informative C64 KERNAL patch that blends PC DOS inspiration with classic Commodore charm, featuring customizable colors, SID detection, and a clean, data-rich startup screen ending with the iconic READY. prompt",
        "PC DOS Style - READY. (UPPERCASE) is a thoughtfully crafted KERNAL patch for the Commodore 64 that blends classic C64 identity with a subtle PC DOS-inspired aesthetic. It allows full control over border, background, and text colors, giving your machine a personalized yet authentic look.\n\nOn startup, it goes beyond the usual screen by detecting and displaying whether your SID chip is a 6581 or 8580, adding a nice hardware-aware touch for enthusiasts. It also calculates and shows the available BASIC memory, just like a proper system overview.\n\nInspired by the clean and informative boot screens of AT&T PC DOS machines, this module delivers a nostalgic hybrid experience—while still proudly ending with the iconic READY. prompt in uppercase form.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x301,
        "dos_ok",
        ":/res/pictures/preview/dosou.gif",
        "PC DOS Style - OK (UPPERCASE)",
        "A stylish and informative C64 KERNAL patch that blends PC DOS inspiration with classic Commodore charm, featuring customizable colors, SID detection, and a clean, data-rich startup screen ending with the iconic OK prompt",
        "PC DOS Style - OK (UPPERCASE) is a thoughtfully crafted KERNAL patch for the Commodore 64 that blends classic C64 identity with a subtle PC DOS-inspired aesthetic. It allows full control over border, background, and text colors, giving your machine a personalized yet authentic look.\n\nOn startup, it goes beyond the usual screen by detecting and displaying whether your SID chip is a 6581 or 8580, adding a nice hardware-aware touch for enthusiasts. It also calculates and shows the available BASIC memory, just like a proper system overview.\n\nInspired by the clean and informative boot screens of AT&T PC DOS machines, this module delivers a nostalgic hybrid experience—while still proudly ending with the iconic OK prompt in uppercase form.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x302,
        "dos_cready",
        ":/res/pictures/preview/dosrc.gif",
        "PC DOS Style - ready. (Capitalized)",
        "A stylish and informative C64 KERNAL patch that blends PC DOS inspiration with classic Commodore charm, featuring customizable colors, SID detection, and a clean, data-rich startup screen ending with the iconic ready. prompt",
        "PC DOS Style - ready. (Capitalized) is a thoughtfully crafted KERNAL patch for the Commodore 64 that blends classic C64 identity with a subtle PC DOS-inspired aesthetic. It allows full control over border, background, and text colors, giving your machine a personalized yet authentic look.\n\nOn startup, it goes beyond the usual screen by detecting and displaying whether your SID chip is a 6581 or 8580, adding a nice hardware-aware touch for enthusiasts. It also calculates and shows the available BASIC memory, just like a proper system overview.\n\nInspired by the clean and informative boot screens of AT&T PC DOS machines, this module delivers a nostalgic hybrid experience—while still proudly ending with the iconic \"ready.\" prompt in lowercase form, offering a subtle contrast to its capitalized title.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x303,
        "dos_cok",
        ":/res/pictures/preview/dosoc.gif",
        "PC DOS Style - Ok (Capitalized)",
        "A stylish and informative C64 KERNAL patch that blends PC DOS inspiration with classic Commodore charm, featuring customizable colors, SID detection, and a clean, data-rich startup screen ending with the iconic Ok prompt",
        "PC DOS Style - Ok (Capitalized) is a thoughtfully crafted KERNAL patch for the Commodore 64 that blends classic C64 identity with a subtle PC DOS-inspired aesthetic. It allows full control over border, background, and text colors, giving your machine a personalized yet authentic look.\n\nOn startup, it goes beyond the usual screen by detecting and displaying whether your SID chip is a 6581 or 8580, adding a nice hardware-aware touch for enthusiasts. It also calculates and shows the available BASIC memory, just like a proper system overview.\n\nInspired by the clean and informative boot screens of AT&T PC DOS machines, this module delivers a nostalgic hybrid experience—while still proudly ending with the iconic Ok prompt.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x400,
        "fakeram",
        ":/res/pictures/preview/fakeram.gif",
        "Fake RAM Test",
        "Displays a nostalgic C64 boot with a fake RAM test, showing “64 KB RAM PASS” and actual free memory before READY.",
        "Fake RAM Test is a playful yet authentic-feeling KERNAL patch for the Commodore 64 that adds a touch of retro theater to your startup experience. Fully customize border, background, and text colors to match your personal style, then enjoy a nostalgic boot sequence where the classic two-line display:\n\nCOMMODORE 64\nBASIC V2\n\nappears before the system seemingly runs a RAM check—progressively counting up to 64KB as if performing a real test. Once “completed,” it smoothly transitions into BASIC, displaying the correctly calculated free memory, just like a genuine system would. It’s a fun, convincing illusion that enhances the vintage charm without altering the core behavior.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x500,
        "commodorelogo",
        ":/res/pictures/preview/clogo.gif",
        "Commodore Logo",
        "Displays a PETSCII Commodore logo at boot before returning to BASIC with the classic READY.",
        "Commodore Logo is a C64 KERNAL patch that adds a nostalgic touch to startup, showing a PETSCII-crafted Commodore logo before returning to BASIC with the iconic READY. prompt, giving retro enthusiasts a classic boot experience.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x580,
        "commodorelogoenhanced",
        ":/res/pictures/preview/clogoe.gif",
        "Commodore Logo (Enhanced)",
        "Enhances the C64 boot experience with full color customization, logo control, and personalized dual-line text before returning to READY.",
        "Commodore Logo (Enhanced) is a polished C64 KERNAL patch that elevates the classic startup experience. It lets you fully customize border, background, and text colors, while giving full control over the Commodore logo’s appearance. Beside the logo, you can display two 24-character lines of text—top and bottom—with independently chosen colors, adding a personal touch to the boot screen. After the display, it gracefully returns to BASIC with the familiar READY. prompt, combining nostalgia with subtle modern flexibility.",
        true,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x510,
        "commodorelogomono",
        ":/res/pictures/preview/clogom.gif",
        "Commodore Monochrome Logo",
        "Displays a customizable monochrome Commodore logo at boot before returning to BASIC with the classic “READY.” prompt",
        "Commodore Monochrome Logo is a classic KERNAL patch for the Commodore 64 that lets you fully customize your screen’s border, background, and text colors. On boot, it greets you with a crisp, monochrome Commodore logo, perfectly matched to your chosen text color, before returning seamlessly to BASIC with the familiar “READY.” prompt—offering a sleek, retro startup experience with a personal touch.",
        false
    },

    {
        0x501,
        "commodorelogo64",
        ":/res/pictures/preview/c64logo.gif",
        "Commodore 64 Logo",
        "Displays a colorful PETSCII Commodore 64 logo on boot with customizable colors, then returns to BASIC with the classic READY. prompt",
        "Commodore 64 Logo is a tasteful KERNAL patch that enhances the classic boot experience while staying true to the spirit of the original machine. It gives you full control over the screen’s border, background, and text colors, allowing you to tailor the visual atmosphere to your personal retro style.\n\nOn startup, the system greets you with a vibrant, PETSCII-crafted Commodore 64 logo rendered in its predefined, carefully designed colors. This fixed artwork preserves the authentic look and feel of classic C64 aesthetics, delivering a nostalgic first impression every time you power on.\n\nAfter displaying the logo, the system smoothly transitions back to BASIC, presenting the familiar READY. prompt—just like the original, but with an added touch of visual charm that celebrates the iconic identity of the Commodore 64.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x581,
        "commodorelogo64enhanced",
        ":/res/pictures/preview/c64logoe.gif",
        "Commodore 64 Logo (Enhanced)",
        "Displays a fully customizable PETSCII Commodore 64 logo with optional colored text before returning to BASIC",
        "Commodore 64 Logo (Enhanced) is a refined KERNAL patch that adds a tasteful and highly customizable visual touch to the classic Commodore 64 startup experience.\n\nOn boot, you’re greeted by a carefully crafted PETSCII Commodore 64 logo that immediately evokes the charm of the original machine, while still feeling fresh and personal. Unlike static implementations, this enhanced version gives you full control over the system’s border, background, and text colors, allowing you to shape the overall aesthetic to match your preferred retro style.\n\nThe logo itself is no longer fixed in appearance—its colors can be fully customized, letting you experiment with anything from authentic factory-inspired palettes to bold, modern reinterpretations. Complementing the logo, the module also allows you to display two lines of text on the right side of the screen, each up to 24 characters long, with independently selectable colors. This provides a perfect space for a signature, system label, or any personal message you’d like to see at startup.\n\nAfter presenting this personalized boot screen, the system smoothly returns to BASIC with the familiar READY. prompt, preserving the original workflow while enhancing the first impression.\n\nFor retro enthusiasts, this patch strikes a satisfying balance between authenticity and personalization—respecting the spirit of the Commodore 64 while giving you just enough control to make it truly your own.",
        true,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x511,
        "commodorelogo64mono",
        ":/res/pictures/preview/c64logom.gif",
        "Commodore 64 Monochrome Logo",
        "Displays a customizable monochrome PETSCII Commodore 64 logo at startup before returning to BASIC with the classic READY. prompt",
        "Commodore 64 Monochrome Logo is a clean and nostalgic KERNAL patch that enhances the classic C64 startup experience without straying from its roots. Designed with retro enthusiasts in mind, it gives you full control over the screen’s border, background, and text colors, allowing you to tailor the visual tone to your exact preference.\n\nOn boot, the system greets you with a carefully crafted PETSCII Commodore 64 logo rendered in a monochrome style, its appearance defined entirely by your chosen text color. This minimalist approach preserves the authenticity of the machine while adding a subtle personal touch. After presenting the logo, the system seamlessly returns to BASIC, ending with the familiar READY. prompt—just as it should.\n\nIt’s a simple yet elegant modification that respects the original spirit of the Commodore 64 while giving its startup screen a refined, customizable identity.",
        false
    },

    {
        0x600,
        "ibmstyle",
        ":/res/pictures/preview/ibm.gif",
        "IBM Style",
        "Displays a PETSCII “C64” logo with customizable colors, evoking classic IBM PC nostalgia before returning to BASIC",
        "IBM Style is a retro-inspired C64 KERNAL patch that brings a touch of classic PC nostalgia to your Commodore 64. On boot, it displays a carefully crafted PETSCII “C64” logo reminiscent of the iconic IBM strip logo from the 1980s, before returning gracefully to BASIC with the familiar READY. prompt. You have full control over the screen’s border, background, and text colors, allowing you to recreate the classic IBM PC look—white or light-gray text on a blue background for a traditional feel, or green text on black for a more hacker-style vibe—giving your startup screen a truly personalized, vintage charm.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x700,
        "c64rainbowbars",
        ":/res/pictures/preview/rainbowbars.gif",
        "C64 Rainbow Bars",
        "Displays a PETSCII C64 logo with colorful rainbow bars on boot, customizable border, background, and text, then returns to BASIC",
        "C64 Rainbow Bars is a nostalgic KERNAL patch for the Commodore 64 that instantly adds a splash of color to your boot screen. On startup, it displays a PETSCII-rendered C64 logo accompanied by vibrant rainbow bars, evoking classic 80s visual flair. While the logo and bars maintain their original preset colors, you can fully customize the screen’s border, background, and text colors, letting you blend personal style with retro authenticity. The display gracefully returns to BASIC with the familiar READY. prompt, making it a perfect mix of flair and functionality for vintage computing enthusiasts.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0x800,
        "floppydiskette",
        ":/res/pictures/preview/floppy.gif",
        "Floppy Diskette Logo",
        "Displays a PETSCII floppy diskette and “COMMODORE 64” on boot with customizable colors before returning to BASIC",
        "Floppy Diskette Logo is a charming retro-inspired C64 KERNAL patch designed for Commodore enthusiasts. On boot, it displays a PETSCII-rendered floppy diskette alongside the classic “COMMODORE 64” text, both sharing the same customizable text color. You have full control over the screen’s border, background, and text colors, letting you tailor the look to your preference. After the display, the system gracefully returns to BASIC with the familiar READY. prompt, combining nostalgia with a touch of personal style.",
        false
    },

    {
        0x900,
        "horizontalcolorbars",
        ":/res/pictures/preview/horbar.gif",
        "Horizontal Color Bars",
        "A retro-inspired Commodore 64 KERNAL patch that displays customizable PETSCII horizontal color bars with a dynamic \"COMMODORE 64\" label and user-defined screen colors before returning to BASIC READY",
        "Horizontal Color Bars is a stylish and nostalgic KERNAL patch for the Commodore 64 that enhances the classic boot experience with a clean, retro aesthetic. Upon startup, it presents three PETSCII-crafted horizontal bars that can be fully customized in color, allowing you to create your own unique visual signature. Beyond that, you have complete control over the screen’s border, background, and text colors, making it easy to match your preferred retro palette.\n\nA particularly nice touch is the “COMMODORE 64” label placed on the right side of the center bar, which dynamically adopts the current text color—blending seamlessly with your chosen theme. The overall presentation feels both minimalistic and authentic, staying true to the spirit of the original machine while offering subtle personalization. After displaying this refined intro screen, the system smoothly returns to BASIC with the familiar READY. prompt, just as any true Commodore enthusiast would expect.",
        true
    },

    {
        0xa00,
        "ultimatemono",
        ":/res/pictures/preview/ultimatem.gif",
        "Commodore Ultimate Monochrome",
        "Displays a PETSCII “Commodore Ultimate” logo in customizable monochrome before returning to BASIC with READY",
        "Commodore Ultimate Monochrome is a sleek KERNAL patch designed for retro enthusiasts who appreciate minimalist elegance on the Commodore 64. On startup, it presents a PETSCII-rendered “Commodore Ultimate” logo in monochrome, perfectly matching the screen’s text color. You have full control over the border, background, and text hues, allowing subtle customization without losing the classic C64 charm. After displaying the logo, the system gracefully returns to BASIC with the familiar READY. prompt, keeping the nostalgic flow intact.",
        false
    },

    {
        0xa80,
        "ultimate",
        ":/res/pictures/preview/ultimate.gif",
        "Commodore Ultimate",
        "Displays a fixed-color PETSCII Commodore Ultimate logo on a customizable C64 screen before returning to BASIC with READY",
        "Commodore Ultimate is a charming KERNAL patch for the C64 that brings a splash of color and nostalgia to the classic boot experience. On startup, it proudly displays a PETSCII-rendered Commodore Ultimate logo in vibrant colors, while giving you full control over the screen’s border, background, and text hues. The logo itself retains its original palette, preserving its iconic look, before gracefully returning to BASIC with the familiar READY prompt. Perfect for retro enthusiasts who enjoy a personalized yet authentic C64 vibe.",
        false,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0xa81,
        "ultimateenhanced",
        ":/res/pictures/preview/ultimatee.gif",
        "Commodore Ultimate (Enhanced)",
        "Displays a fully customizable PETSCII Commodore Ultimate logo with adjustable colors, optional two-line text, and personalized border, background, and text colors before returning to BASIC with READY",
        "Commodore Ultimate (Enhanced) is a nostalgic C64 KERNAL patch that lets retro enthusiasts fully personalize their startup experience: you can customize the screen’s border, background, and text colors, tweak the PETSCII-rendered Commodore Ultimate logo with independent colors for both the classic Commodore symbol and the “Ultimate” lettering, and even add two lines of eight-character text in any color to the right of the logo, before smoothly returning to BASIC with the familiar READY. prompt.",
        true,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },

    {
        0xb01,
        "commodoremono",
        ":/res/pictures/preview/ctextm.gif",
        "Commodore Text Monochrome",
        "A retro-inspired C64 KERNAL patch that centers a monochrome PETSCII Commodore Text logo matching the text color while allowing full border, background, and text customization before returning to BASIC",
        "The Commodore Text Monochrome KERNAL patch is a sleek, retro-inspired enhancement for your Commodore 64, designed for enthusiasts who appreciate minimalist style. On boot, it displays a PETSCII-rendered Commodore Text logo, perfectly centered and matching the screen’s text color, creating a clean, monochrome aesthetic. You have full control over the border, background, and text colors, allowing you to customize the visual tone to your liking. Once the logo is shown, the system gracefully returns to BASIC with the familiar READY. prompt, preserving the classic C64 experience while adding a subtle, stylish touch.",
        false
    },

    {
        0xb00,
        "commodore",
        ":/res/pictures/preview/ctext.gif",
        "Commodore Text",
        "A customizable C64 KERNAL patch that displays a centered PETSCII Commodore text logo with adjustable colors before returning to BASIC",
        "Commodore Text is a sleek and nostalgic KERNAL patch for the C64 that lets retro enthusiasts fully personalize their boot screen experience. On startup, it displays a horizontally centered PETSCII Commodore text logo with customizable top and bottom colors, while giving you full control over the screen’s border, background, and text hues. After the visual flourish, the system gracefully returns to BASIC with the familiar READY. prompt, combining classic C64 charm with a touch of modern customization.",
        true,
        CardItem::AccessType::Locked,
        "https://c64kernal.com/modules"
    },
};

#endif // MODULES_H
