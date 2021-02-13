# Lasso Project for CS101

## Compile and run

### Linux or MacOS

```bash
s++ -o lasso -g **.cpp
./lasso
```

### Windows

```powershell
mingw32-g++.exe -std=c++0x -Wall -g -c test.cpp -o test
mingw32-g++.exe -std=c++0x -Wall -g -c test1.cpp -o test1
mingw32-g++.exe  -o test test test1 -lsprite -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

## Additions made

- Coin now moves in a parabolic path at a random angle restricted between 70 to 120 degrees
- something
- something
- something
- something
