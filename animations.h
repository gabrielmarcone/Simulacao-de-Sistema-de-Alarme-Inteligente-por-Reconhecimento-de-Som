void run_animation(const uint32_t frames[][25], int num_frames, int delay_ms);
uint32_t matrix_rgb(double g, double r, double b);

void animation_alarm_off() {
    uint32_t green_frames[5][25] = {
        {
            matrix_rgb(0.5, 0, 0), 0, 0, 0, 0, 
            matrix_rgb(0.5, 0, 0), 0, 0, 0, 0,
            matrix_rgb(0.5, 0, 0), 0, 0, 0, 0,
            matrix_rgb(0.5, 0, 0), 0, 0, 0, 0,
            matrix_rgb(0.5, 0, 0), 0, 0, 0
        },
        {
            0, matrix_rgb(0.5, 0, 0), 0, 0, 0,
            0, matrix_rgb(0.5, 0, 0), 0, 0, 0,
            0, matrix_rgb(0.5, 0, 0), 0, 0, 0,
            0, matrix_rgb(0.5, 0, 0), 0, 0, 0,
            0, matrix_rgb(0.5, 0, 0), 0, 0
        },
        {
            0, 0, matrix_rgb(0.5, 0, 0), 0, 0,
            0, 0, matrix_rgb(0.5, 0, 0), 0, 0,
            0, 0, matrix_rgb(0.5, 0, 0), 0, 0,
            0, 0, matrix_rgb(0.5, 0, 0), 0, 0,
            0, 0, matrix_rgb(0.5, 0, 0), 0
        },
        {
            0, 0, 0, matrix_rgb(0.5, 0, 0), 0,
            0, 0, 0, matrix_rgb(0.5, 0, 0), 0,
            0, 0, 0, matrix_rgb(0.5, 0, 0), 0,
            0, 0, 0, matrix_rgb(0.5, 0, 0), 0,
            0, 0, 0, matrix_rgb(0.5, 0, 0)
        },
        {
            0, 0, 0, 0, matrix_rgb(0.5, 0, 0),
            0, 0, 0, 0, matrix_rgb(0.5, 0, 0),
            0, 0, 0, 0, matrix_rgb(0.5, 0, 0),
            0, 0, 0, 0, matrix_rgb(0.5, 0, 0),
            0, 0, 0, 0
        }
    };
    run_animation(green_frames, 5, 100);
}

void animation_alarm_triggered() {
    uint32_t alarm_frames[9][25] = {
        {
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), 
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0)
        },
        {
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), 
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0)
        },
        {
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), 
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0)
        },
        {
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), 
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0)
        },
        {
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), 
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0)
        },
        {
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), 
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0)
        },
        {
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), 
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0)
        },
        {
            matrix_rgb(0, 0.05, 0), matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), 
            matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0)
        },
        {
            matrix_rgb(0, 0.8, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), 
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0),
            matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0), matrix_rgb(0, 0.4, 0)
        }
    };
    run_animation(alarm_frames, 9, 30);
}