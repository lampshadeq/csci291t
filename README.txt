CSCI 291T - Spring 2017
Chicken Cheese Crusader

Team Chicken:
  Carlos Moreno
  Akhil Stanislavose
  
Story:
  Years have passed since the Great War. In the aftermath,
  the Chickens have become enslaved by their nemesis, the Farmers.
  But now, one brave Chicken will attempt the impossible: escape!
  He will need your help to solve the traps placed by the Farmer
  Overlords. Will you join this Chicken on his crusade to save his
  people by throwing cheese???
  
Controls:
  - use the directional buttons to move the player around the maze
  - collect the cheese in order to use it against the obstacles
  - use the space bar to launch your cheese projectiles
  - use the backspace key or escape key to go back to the main menu
  
Implementation:
  We utilized the C++ programming language in combination with
  OpenGL. In addition, many libraries were used such as irrKlang for
  sound, GLU/GLUT for easier OpenGL, SOIL for easy texture, and
  GLEW for shader programming. The engine for this game is based
  on the game engine developed during class.
  
  Beyond the base game engine, we utilized a generic level loader that
  made level design and implementation simple. Moreover, we made use
  of particles and a custom shader program for changing their RGB
  values.
  
  In total, 5 levels were created for the user. Completing all 5
  levels will return the user to the main menu. During the game,
  the user can press the backspace/escape key to display the
  pause menu, which allows to the resume the game, return to the
  main menu, or quit.
  
  Future work includes fixing minor bugs, adding more obstacles
  and weapons, as well as a possible boss fight.