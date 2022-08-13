# OpenGL Learning

### Markdown Style
Markdown file may look weird if you don't install my own style, get style.css [here](https://github.com/HxxWorkAccount/Markdown-Google-Style).

### Build Project
If you want to build this project, you need to change the `CMakeLists.txt` in root folder to import dependencies correctly (I only write that for my M1-MacBook).

<!-- TODO Use find_package to adapt to each platform -->

1. Open Terminal and `cd` to root folder
1. New folder in root `./Build`
1. Cmake `cmake --build ./Build --config Debug --target all -j 10`
1. Run executable target `./Build/Source/Run`


</br>
</br>
</br>
</br>
</br>
</br>
---End---
