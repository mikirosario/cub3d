#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct  data_s
{
        void    *mlx_ptr;
        void    *mlx_win;
}               data_t;

int    stop(int key, void *param)
{
    printf("DEJA DE TOCARME\n");
    return (0);
}

int main(void)
{
    data_t  data;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello World")) == NULL)
        return (EXIT_FAILURE);
    mlx_key_hook(data.mlx_win, stop, (void *)0);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);

}
