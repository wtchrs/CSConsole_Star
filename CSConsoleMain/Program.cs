using System;
using System.Runtime.InteropServices;

namespace CSConsoleMain
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            IntPtr star = CStarLib.MakeStar(20, 20, 0, 0, 0, 0, 20);

            for (int y = 0; y < 40; y++) {
                for (int x = 0; x < 40; x++) {
                    if (CStarLib.StarCheckInside(star, x, y)) {
                        Console.Write("* ");
                    }
                    else {
                        Console.Write("  ");
                    }
                }

                Console.WriteLine();
            }

            CStarLib.DeleteStar(star);
        }
    }

    internal class CStarLib
    {
        [DllImport("CStarMarshall.dll", EntryPoint = "make_star")]
        public static extern IntPtr MakeStar(
            double x, double y, double vx, double vy, double angle, double rotate, double ldistance, double ratio = 0.36);

        [DllImport("CStarMarshall.dll", EntryPoint = "make_colored_star")]
        public static extern IntPtr MakeColoredStar(
            ulong color, double x, double y, double vx, double vy, double angle, double rotate, double ldistance,
            double ratio = 0.36);

        [DllImport("CStarMarshall.dll", EntryPoint = "delete_star")]
        public static extern void DeleteStar(IntPtr p_star);

        [DllImport("CStarMarshall.dll", EntryPoint = "star_neg_vx")]
        public static extern void StarNegvx(IntPtr p_star);

        [DllImport("CStarMarshall.dll", EntryPoint = "star_neg_vy")]
        public static extern void StarNegvy(IntPtr p_star);

        [DllImport("CStarMarshall.dll", EntryPoint = "star_move_for_time")]
        public static extern void StarMoveForTime(IntPtr p_star, double time);

        [DllImport("CStarMarshall.dll", EntryPoint = "star_get_center_x")]
        public static extern double StarGetCenterX(IntPtr p_star);

        [DllImport("CStarMarshall.dll", EntryPoint = "star_get_center_y")]
        public static extern double StarGetCenterY(IntPtr p_star);

        [DllImport("CStarMarshall.dll", EntryPoint = "star_get_color")]
        public static extern ulong StarGetColor(IntPtr p_star);

        [DllImport("CStarMarshall.dll", EntryPoint = "star_get_points")]
        public static extern IntPtr StarGetPoints(IntPtr p_star);

        [DllImport("CStarMarshall.dll", EntryPoint = "star_check_inside")]
        public static extern bool StarCheckInside(IntPtr p_star, double x, double y);
    }
}