#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mlx.h>

typedef struct  data_s
{
        void    *mlx_ptr;
        void    *mlx_win;
        void    *mlx_img;
}               data_t;

static data_t  data;

void   delay(int milisecs)
{
    clock_t start_time = clock();
    while (clock() < start_time + milisecs)
    ;
}

void cls()
{
    int x = 0;
        while (x <= 640) //clearscreen
        {
            int y = 480;
            while (y)
            {
                mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y--, 0x000000);
            }
            x++;
        }
}

int    test(int key, void *param)
{
    printf("hola\n");
    int x = 0;
    int y = 0;
    char static stayOut = 'N';
    (void)param;
    (void)key;

        int colorR = 000255000000;
        int colorG = 000000255000;
        int colorB = 000000000255;
        int color;
        if (/*key* == 39 &&*/stayOut == 'N')
        {
            cls();
            stayOut = 'Y';
            // int colorT = 000000000000;
                x = 0;
                color = colorB;
                while (x <= 640)
                {
                    y = 480;
                    while (y >= 0)
                    {
                        mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y, color);
                        y--;
                    }
                    x++;
                    if (x == 213)
                        color = colorG;
                    else if (x == 427)
                        color = colorR;
                }
                x = (640 / 2) - 80;
                delay(100000);
        }
        else if (stayOut == 'Y')
        {
            cls();
            stayOut = 'N';
            x = (640 / 2) - 80;
            color = colorR;
            while (x <= (640 / 2) + 80)
            {
                y = (480 / 2) + 80;
                while (y >= (480 / 2) - 80)
                {
                    mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y, color);
                    y--;
                    //delay(250); //encuentra el 'redraw' de miniLibX
                    //el draw está separado de pixel_put, cabrón
                }
                x++;
                if (x == 293)
                    color = colorG;
                else if (x == 347)
                    color = colorB;
                //else if (color == colorB)
                    //  color = colorR;
            }
        }

    return (0);
        
}

int    stop(int key, void *param)
{
    int x = 0;
    int y = 0;
    int size = 350;
    char static stayOut = 'N';
    int static check = 1;
    mlx_string_put(data.mlx_ptr, data.mlx_win, 0, 0, 0x00FF0000, "CHIVATO");
    (void)param;
    data.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "medium_oren.XPM", &size, &size);
    if ((key == 0x24 || key == 0x31) && stayOut == 'N')
    {
        stayOut = 'O';
        mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.mlx_img, x, y);
    }
    else if ((key == 0x24 || key == 0x31) && stayOut == 'O')
    {
        stayOut = 'Y';
        printf("%d", mlx_string_put(data.mlx_ptr, data.mlx_win, 420, 180, 0xFF0000, "DEJA DE TOCARME"));
    }
    else if (key == 0x35 || key == 0x0)
    {
        mlx_destroy_image(data.mlx_ptr, data.mlx_img);
        mlx_destroy_window(data.mlx_ptr, data.mlx_win);
        exit(0);
    }
    else if (key == 0x8)
    {
        cls();
        stayOut = 'N';
    }
    else if (key == 0xF)
    {
        cls();
        stayOut = 'N';
        int colorR = 000255000000;
        int colorG = 000000255000;
        int colorB = 000000000255;
        int color;
        if (check)
        {
            // int colorT = 000000000000;
                x = 0;
                color = colorB;
                while (x <= 640)
                {
                    y = 480;
                    while (y >= 0)
                    {
                        mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y, color);
                        y--;
                    }
                    x++;
                    if (x == 213)
                        color = colorG;
                    else if (x == 427)
                        color = colorR;
                }
                x = (640 / 2) - 80;
                delay(100000);
        }
        else
        {
            x = (640 / 2) - 80;
            color = colorR;
            while (x <= (640 / 2) + 80)
            {
                y = (480 / 2) + 80;
                while (y >= (480 / 2) - 80)
                {
                    mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y, color);
                    y--;
                    //delay(250); //encuentra el 'redraw' de miniLibX
                    //el draw está separado de pixel_put, cabrón
                }
                x++;
                if (x == 293)
                    color = colorG;
                else if (x == 347)
                    color = colorB;
                //else if (color == colorB)
                    //  color = colorR;
            }
        }
        check = check ^ 1;
    }
    return (0);
}

int main(void)
{

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello World")) == NULL)
        return (EXIT_FAILURE);
    mlx_hook(data.mlx_win, 2, 0, stop, (void *)0);
    mlx_hook(data.mlx_win, 17, 0, stop, (void *)0);
    mlx_loop_hook(data.mlx_ptr, test, (void *)0);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);

}
