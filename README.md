<h1>SFML Platformer</h1>

<p> A 2D platformer game developed with SFML for school.</p>

<br>

<p>
<img width=500 src="https://github.com/user-attachments/assets/8714f35c-76c8-4b94-a496-2f1b49b87fd7">
</p>

[Overview](#overview) | [Controls](#controls) | [Textfile Level Editor](#textfile-level-editor) | [Asset Credits](#asset-credits) | [Class Diagram](#class-diagram)

---

> [!IMPORTANT]
> Please note that images and graphical assets used in this project are not included in this repository due to licensing restrictions.
> Some assets were purchased under individual licenses and cannot be redistributed.
> 
> Credit and links to the assets used can be found [here](#asset-credits)

# Overview
The goal of the game is to reach the portal as fast as possible while avoiding/defeating enemies.
Use 'WASD' or arrows for movement. 'J' to attack.

The game features a lightweight level-editor.

## Controls
- Movement: `W` `A` `S` `D` or arrows
- Jumping: `Spacebar`
- Attack: `J`

## Textfile level editor
The level gets loaded from a .txt file. Edit the textfile to change the level. 
Different numbers correspond to different GameObjects.

<img width=450 src="https://github.com/user-attachments/assets/22151d4a-ba6f-48fd-ab37-bf667c89cfdd">

<p>
  
| Number | Game Object |
| ------ | ----------- |
| 0 | Empty |
| 1 | Platform |
| 2 | Portal |
| 3 | Player |
| 4 | Enemy |

</p>

# Asset Credits
- **Player:**
  - Pixel Prototype Player Sprites by Dead Revolver - [Link to asset](https://deadrevolver.itch.io/pixel-prototype-player-sprites)

- **Enviroment:**
  - Eclipse — Environment Asset by Bruno Farias - [Link to asset](https://bruno-farias.itch.io/eclipse)

- **Background:**
  - Mountain Dusk Parallax Background by ansimuz - [Link to asset](https://ansimuz.itch.io/mountain-dusk-parallax-background)

- **Font:**
  - Gravity Font Pack by jotson - [Link to asset](https://jotson.itch.io/gravity-pixel-font)

# Class-diagram
<img src="https://github.com/OscarLarm/sfml-platformer/blob/ee4b01846e6eadc6708de2ce5bd9977f625eff77/diagram/uml-diagram.png">
