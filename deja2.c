#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mlx.h>

typedef struct  data_s
{
        void    *mlx_ptr;
        void    *mlx_win;
}               data_t;

data_t  data;

int    stop(int key, void *param)
{
    srand(time(NULL));
    int x = rand() % 320;
    int y = rand() % 240;
    mlx_string_put(data.mlx_ptr, data.mlx_win, x, y, 255, "DEJA DE TOCARME");
    if (key == 0x35)
    {
        mlx_destroy_window(data.mlx_ptr, data.mlx_win);
        exit(0);
    }
    return (0);
}

int main(void)
{
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello World")) == NULL)
        return (EXIT_FAILURE);
    mlx_key_hook(data.mlx_win, stop, (void *)0);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);

}
