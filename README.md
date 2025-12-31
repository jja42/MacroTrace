# Macro Trace

A lightweight Windows macro recorder and player built in C, with web-based sharing.

Users can record keyboard and mouse events, save them as JSON macros, and share them through a static website.  

Supports almost all input types, except for a few special keyboard keys and extra mouse buttons.

---

## Features

- Record and replay keyboard and mouse events.
- Supports special keys: Shift, Ctrl, Alt, Windows key, Function keys, etc.
- Precise timing using high-resolution counters.
- Upload macros to a static website via GitHub Issue Form or the site upload button.
- Automatic indexing of uploaded macros with descriptions.
- Cross-user macro sharing without a backend server.

---

## Quick Start

Download the latest release here:  
[**Latest Release**](https://github.com/jja42/MacroTrace/releases/tag/Release)

Visit the Macro Library for more files or to upload your own:  
[**Macro Library**](https://jja42.github.io/MacroTrace/)

---

## Usage

### Recording

1. Run the executable and choose **Record** (type `1` or `Record`).  
2. Press the keys or mouse buttons you want to record.  
3. Press **Esc twice** to finish recording.  
4. Give your macro a name and save the file.

### Replaying

1. Run the executable and choose **Replay** (type `2` or `Replay`).  
2. Enter the name of the macro file you want to replay.  
3. Press **Caps Lock twice** to replay after loading.  
4. Press **Esc twice** to stop replaying.

### Macro Library Site

[**Macro Library**](https://jja42.github.io/MacroTrace/)

- Browse macros uploaded by other users.  
- Download macros directly.  
- Upload your own macros to share with the community.

---

## Site Features

- View macro names and descriptions.  
- Download macros directly in JSON format.  
- Upload new macros with a description.  
- Automatic updates via GitHub Actions to include new submissions.

---

## How to Upload

1. Submit macros via the **GitHub Issue Form** or the **Upload button** on the site.  
2. Provide a descriptive **name** and **description** for your macro.  
3. Submit the `.json` macro file.  

---

## Motivation

I wanted to make something simple to use but with a lot of possibility. What better way than to let the community decide what a project can do?
MacroTrace keeps things straightforward with a clean command line interface and maximizes performance with an optimized C codebase.
No Installation. No tweaks. Open, record and playback. Easy to import new files and export them for others to use.

---

## Contributing
If you'd like to contribute, please fork the repository and open a pull request.
4. GitHub Actions will automatically download your JSON, update the macro index, and deploy it to the site.

---

**Enjoy recording, replaying, and sharing your macros!**
