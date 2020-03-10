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
    int matrix[480][640] = {}
    
    int x = 320 - 100;
    int y = 240 - 100;
    int i = 100;
    while (i--)
    {
        mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y++, 255);
        if (i == 0 && x != 240)
        {
            i = 100;
            x++;
        }
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
