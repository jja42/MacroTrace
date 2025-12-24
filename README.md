# Macro Trace

- A lightweight Windows macro recorder and player with web-based sharing.
- Built in C.
- Users can record keyboard and mouse events, save them as JSON macros, and share them through a static website. 
- Supports almost all Input Types, barring only special keyboard specific keys and extra Mouse Buttons.

---

## Features

- Record and replay keyboard and mouse events.
- Supports special keys: Shift, Ctrl, Alt, Windows key, Function keys, etc.
- Precise timing using high-resolution counters.
- Upload macros to a static website via GitHub Issue Form.
- Automatic indexing of uploaded macros with descriptions.
- Cross-user macro sharing without a backend server.

---

## Installation

Simply download the latest release
[Latest](https://github.com/jja42/MacroTrace/releases/tag/Release)

To find more Files or Upload your own visit the Site
[Macro Library](https://jja42.github.io/MacroTrace/)

---

## Usage

Follow the prompts in the program after running the executable file.
Here's a quick guide.

Recording
- Type 1 or Record to Record
- Press whichever inputs you want to record
- Use Esc Twice to Finish Recording
- Name your file

Replaying
- Type 2 or Replay to Replay
- Type the Name of the File you want to Replay
- Use Caps Lock Twice to Replay a file after loading it
- Use Esc Twice to Finish Replaying

Site
In addition to a program that can record and replay, you can visit the Macro Library to
- Find additional Macros
- Upload your own Macros
- See what others have created

---

## Site Features:

- View macros and their descriptions.
- Download macros directly.
- Upload Macros
- Automatically Updates via Github Workflow to include new submissions

---

## How to Upload

- Users can submit macros either via a GitHub Issue Form or the Upload Button on the Site
- Provide a name and description for the macro.
- Submit .json macro files.
- GitHub Actions automatically downloads the JSON, updates the index, and deploys it to the static site.
