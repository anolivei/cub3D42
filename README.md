# cub3D42
My first RayCaster with miniLibX<br>


First of all, install minilibX in you Linux:<br>
```
sudo apt-get install -y libxext-dev && sudo apt-get install -y libxrandr-dev && sudo apt-get install -y libx11-dev && sudo apt-get install -y libbsd-dev && sudo apt-get install -y libssl-dev

cd /usr/local/man/ && sudo mkdir man1

cd ~ && git clone https://github.com/42Paris/minilibx-linux.git && cd minilibx-linux && make

sudo cp man/man1/* /usr/local/man/man1/ && sudo cp libmlx.a /usr/local/lib/ && sudo cp mlx.h /usr/local/include/
```
<br>

So, type make to compile the program
```
make
```

And them, execute Cub3D with a file .cub (ex: maps/map0.cub)
```
./cub3D maps/map0.cub
```

For more information about Cub3D: http://bit.ly/cub3D42<br>
<br>
