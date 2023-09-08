/*
Date: 20230904
Author: Professor Ying-Chih Lai 
Adstract:
The motion detect example code from Professor Lai.

*/ 

// Motion state detect
// Falls
if (Math.Abs(att_com[0]) > falls_thd || Math.Abs(att_com[1]) > falls_thd)
{
    dt_falls = dt_falls + dt;
    if (dt_falls > falls_time_thd)
    {
        falls_flag = 1;
        stand_flag = 0;
        walk_flag = 0;
        sit_flag = 0;
        step_index = 0;
        walk_index = 0;
        walk_cd_timer = 0;
        //motion_state = 4;
        //radioButton4.Checked = true;
    }
}
else
{
    falls_flag = 0;
    dt_falls = 0;
}

// Other motion
if (a_abs[0] > motion_acc_thd && motion_index == 0)
{
    motion_index = 3;

}
if (motion_index > 0)
{
    dt_motion = dt_motion + dt;
    if (a_abs[0] > motion_acc_thd)
        motion_index = 3;
    else
        motion_index--;

    // Walk               
    if (att_com[0] > roll_max)
    {
        roll_max = att_com[0];
    }
    else if ((att_com[0] < roll_max - 3) && walk_index != 1)
    {
        walk_cd_timer = walk_cd_thd;  // reset cd_timer
        roll_max = -45;     // reset roll_max
        step_index++;
        walk_index = 1;
    }
    if (att_com[0] < roll_min)
    {
        roll_min = att_com[0];
    }
    else if ((att_com[0] > roll_min + 3) && walk_index != 2)
    {
        walk_cd_timer = walk_cd_thd;  // reset cd_timer
        roll_min = 45;     // reset roll_min
        step_index++;
        walk_index = 2;
    }
    if (step_index > 0)
    {
        walk_cd_timer = walk_cd_timer - dt; // counterdown
        if (step_index > 3)
        {
            walk_flag = 1;
            stand_flag = 1; // walk olny in stand state
            sit_flag = 0;
        }
        if (walk_cd_timer < 0)
        {
            step_index = 0;
            walk_flag = 0;
            walk_index = 0;
        }
    }

    // Stand up and sit down
    // head velocity
    v_n = v_n + a_ned[0] * 9.8 * dt;
    if ((v_n > 0 && a_ned[0] < -0.02) || (v_n < 0 && a_ned[0] > 0.02))
    {
        v_n = 0;
    }
    if (v_n < -1 && Math.Abs(att_com[1] - pitch_still) > 15)
    {
        //v_n = 0;
        updwon_index = 2;   // sit down
        sit_flag = 1;
        stand_flag = 0;
        step_index = 0;
        walk_index = 0;
        walk_flag = 0;
    }
    else if (v_n > 1 && Math.Abs(att_com[1] - pitch_still) > 15)
    {
        //v_n = 0;
        updwon_index = 1;   // stand up
        sit_flag = 0;
        stand_flag = 1;
    }
    /*  // pitch
    if (att_com[1] > pitch_still + 20)
    {
        updwon_index = 2;   // sit down
        sit_flag = 1;
        stand_flag = 0;
        step_index = 0;
        walk_index = 0;
        walk_flag = 0;
    }
    else if (att_com[1] < pitch_still - 20)
    {
        updwon_index = 1;   // stand up
        sit_flag = 0;
        stand_flag =1;
    }
    */

}
else    // motionless
{
    v_n = 0;
    dt_motion = 0;
    pitch_still = att_com[1];
    if (step_index > 0)
    {
        walk_cd_timer = walk_cd_timer - dt; // counterdown
        if (step_index > 3)
        {
            walk_flag = 1;
            stand_flag = 1; // walk olny in stand state
            sit_flag = 0;
        }
        if (walk_cd_timer < 0)
        {
            step_index = 0;
            walk_index = 0;
            walk_flag = 0;
        }
    }
}