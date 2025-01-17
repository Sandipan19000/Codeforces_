#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int screen_option = 0;
int mouse_x, mouse_y, Win_x, Win_y, object_select;
static int view_state = 0;
int spin, spinboxes;
int win, player, computer, start_game;
GLUquadricObj *Cylinder;

int box_map[9];

int object_map[9][2] = {{-6, 6}, {0, 6}, {6, 6}, {-6, 0}, {0, 0}, {6, 0}, {-6, -6}, {0, -6}, {6, -6}};

position determines the box no.static int box[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

void init_game(void)
{
    int i;

    for (i = 0; i < 9; i++)
    {
        box_map[i] = 0;
    }

    win = 0;
    start_game = 1;
}

int check_move(void)
{

    int i, t = 0;

    for (i = 0; i < 8; i++)
    {

        t = box_map[box[i][0]] + box_map[box[i][1]] + box_map[box[i][2]];
        if ((t == 3) || (t == -3))
        {

            spinboxes = i;

            return (1);
        }
    }

    t = 0;

    for (i = 0; i < 8; i++)
    {
        t = t + abs(box_map[box[i][0]]) + abs(box_map[box[i][1]]) + abs(box_map[box[i][2]]);
    }

    if (t == 24)
        return (2);

    return (0);
}

int blocking_win()
{
    int i, t;
    for (i = 0; i < 8; i++)
    {
        t = box_map[box[i][0]] + box_map[box[i][1]] + box_map[box[i][2]];
        and one is vacant if ((t == 2) || (t == -2))
        {

            if (box_map[box[i][0]] == 0)
                box_map[box[i][0]] = computer;
            if (box_map[box[i][1]] == 0)
                box_map[box[i][1]] = computer;
            if (box_map[box[i][2]] == 0)
                box_map[box[i][2]] = computer;

            return (1);
        }
    }

    return (0);
}

int check_corner(void)
{
    int i;
    if (box_map[0] == 0)
    {
        box_map[0] = computer;
        i = 1;
        return (1);
    }
    if (box_map[2] == 0)
    {
        box_map[2] = computer;
        i = 1;
        return (1);
    }
    if (box_map[6] == 0)
    {
        box_map[6] = computer;
        i = 1;
        return (1);
    }
    if (box_map[8] == 0)
    {
        box_map[8] = computer;
        i = 1;
        return (1);
    }
    return (0);
}

int check_row(void)
{

    if (box_map[4] == 0)
    {
        box_map[4] = computer;
        return (1);
    }

    if (box_map[1] == 0)
    {
        box_map[1] = computer;
        return (1);
    }
    if (box_map[3] == 0)
    {
        box_map[3] = computer;
        return (1);
    }
    if (box_map[5] == 0)
    {
        box_map[5] = computer;
        return (1);
    }
    if (box_map[7] == 0)
    {
        box_map[7] = computer;
        return (1);
    }

    return (0);
}

int computer_move()
{
    if (blocking_win() == 1)
        return (1);
    if (check_corner() == 1)
        return (1);
    if (check_row() == 1)
        return (1);
    return (0);
}

void Sprint(int x, int y, char *st)
{
    int l, i;

    l = strlen(st);

    glRasterPos2i(x, y);

    or (i = 0; i < l; i++)
    {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
    }
}

static void TimeEvent(int te)
{

    spin++;

    if (spin > 360)
        spin = 180;

    glutPostRedisplay();

    glutTimerFunc(8, TimeEvent, 1);
}

void init(void)
{

    glClearColor(0.082, 0.125, 0.169, 0.0);

    start_game = 0;
    win = 0;

    Cylinder = gluNewQuadric();
    gluQuadricDrawStyle(Cylinder, GLU_FILL);
    gluQuadricNormals(Cylinder, GLU_SMOOTH);
    gluQuadricOrientation(Cylinder, GLU_OUTSIDE);
}

void Draw_O(int x, int y, int z, int a)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(a, 0, 1, 0);
    glutSolidTorus(0.5, 2.0, 20, 16);
    glPopMatrix();
}

void Draw_X(int x, int y, int z, int a)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glPushMatrix();
    glRotatef(a, 0, 1, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(45, 1, 0, 0);
    glTranslatef(0, 0, -3);
    gluCylinder(Cylinder, 0.5, 0.5, 6, 16, 16);
    glPopMatrix();
    glPushMatrix();
    glRotatef(a, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(315, 1, 0, 0);
    glTranslatef(0, 0, -3);
    gluCylinder(Cylinder, 0.5, 0.5, 6, 16, 16);
    glPopMatrix();
    glPopMatrix();
}

void display(void)
{

    if (screen_option == 3)
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(0.0, 1.0, 0.0);

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        glDisable(GL_COLOR_MATERIAL);

        glColor3f(1.0, 1.0, 1.0);

        Sprint(-3, -2, "To Start the game, press right button and select start game");

        glutSwapBuffers();
    }

    else if (screen_option == 0)
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        glDisable(GL_COLOR_MATERIAL);

        glColor3f(1.0, 1.0, 1.0);

        Sprint(-2, 3, "TIC - TAC - TOE");
        Sprint(-2, 1, "A Game created by");
        Sprint(-3, -1, "Vyom Chopra");
        Sprint(2, -1, "101917060");
        Sprint(-3, -2, "Naman Aggarwal");
        Sprint(2, -2, "101917077");
        Sprint(-3, -3, "Ishav Garg");
        Sprint(2, -3, "101917074");
        Sprint(-3, -5, "Right Click to Start the Game");

        glutSwapBuffers();
    }

    else
    {
        int ix, iy;
        int i;
        int j;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        glDisable(GL_COLOR_MATERIAL);

        glColor3f(1.0, 0.0, 0.0);

        if (win == 1)
            Sprint(-2, 1, "Congratulations!! You Won :)");
        if (win == -1)
            Sprint(-2, 1, "Computer Won :(");
        if (win == 2)
            Sprint(-2, 1, "It's a Tie");

        if (view_state == 1)
        {
            glColor3f(1.0, 0.0, 0.0);
            Sprint(-3, 8, "Perspective View");
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60, 1, 1, 30);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }

        else
        {
            glColor3f(1.0, 0.0, 0.0);
            Sprint(-2, 8, "Ortho View");
        }

        gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);

        for (ix = 0; ix < 4; ix++)
        {
            glPushMatrix();
            glColor3f(1, 1, 1);
            glBegin(GL_LINES);
            glVertex2i(-9, -9 + ix * 6);
            glVertex2i(9, -9 + ix * 6);
            glEnd();
            glPopMatrix();
        }

        for (iy = 0; iy < 4; iy++)
        {
            glPushMatrix();
            glColor3f(1, 1, 1);
            glBegin(GL_LINES);
            glVertex2i(-9 + iy * 6, 9);
            glVertex2i(-9 + iy * 6, -9);
            glEnd();
            glPopMatrix();
        }

        for (i = 0; i < 9; i++)
        {
            j = 0;

            if (abs(win) == 1)
            {

                if ((i == box[spinboxes][0]) || (i == box[spinboxes][1]) || (i == box[spinboxes][2]))
                {
                    j = spin;
                }
                else
                    j = 0;
            }

            if (box_map[i] == 1)
                Draw_X(object_map[i][0], object_map[i][1], -1, j);
            if (box_map[i] == -1)
                Draw_O(object_map[i][0], object_map[i][1], -1, j);
        }

        glutSwapBuffers();
    }
}

void reshape(int w, int h)
{
    Win_x = w;
    Win_y = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {

    case 'v':
    case 'V':
        view_state = abs(view_state - 1);
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void mouse(int button, int state, int x, int y)
{

    mouse_x = (18 * (float)((float)x / (float)Win_x)) / 6;
    mouse_y = (18 * (float)((float)y / (float)Win_y)) / 6;

    object_select = mouse_x + mouse_y * 3;

    if (start_game == 0)
    {

        if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        {
            player = -1;
            computer = 1;
            init_game();
            return;
        }
    }

    if (start_game == 1)
    {

        if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        {

            if (win == 0)
            {

                if (box_map[object_select] == 0)
                {

                    box_map[object_select] = player;

                    win = check_move();

                    if (win == 1)
                    {
                        start_game = 0;
                        return;
                    }

                    computer_move();

                    win = check_move();
                    if (win == 1)
                    {
                        win = -1;
                        start_game = 0;
                    }
                }
            }
        }
    }

    if (win == 2)
        start_game = 0;
}

void menu(int choice)
{
    switch (choice)
    {

    case 1:
        screen_option = 1;
        glutMouseFunc(mouse);
        break;

    case 2:
        view_state = abs(view_state - 1);
        break;

    case 3:
        screen_option = 3;
        glutMouseFunc(mouse);
        break;

    case 4:
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(850, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow(argv[0]);
    glutSetWindowTitle("Tic Tac Toe 3D");
    init();

    glutCreateMenu(menu);
    glutAddMenuEntry("Start Game", 1);
    glutAddMenuEntry("Prespective View", 2);
    glutAddMenuEntry("Help", 3);
    glutAddMenuEntry("Quit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(50, TimeEvent, 1);

    glutMainLoop();
    return 0;
}