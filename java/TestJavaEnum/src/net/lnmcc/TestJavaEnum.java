package net.lnmcc;

public class TestJavaEnum {

    static enum WorkDay {
        Mon("Monday"),
        Tue("Tuesday"),
        Wed("Wednesday"),
        Thu("Thursday"),
        Fri("Friday");

        private String mDay;

        private WorkDay(String day) {
            mDay = day;
        }

        @Override
        public String toString() {
            return mDay;
        }
    }

    public static void main(String[] args) {
        WorkDay[] workDays = WorkDay.values();

        System.out.println("------WorkDay------");
        for (int i = 0; i < workDays.length; i++) {
            WorkDay workDay = workDays[i];
            System.out.println(workDay.toString());
        }

        System.out.println("------Ordinal------");

        for (int i = 0; i < workDays.length; i++) {
            WorkDay workDay = workDays[i];
            System.out.println(workDay.toString() + "'s ordinal is "
                    + workDay.ordinal());
        }

        System.out.println("------ValueOf------");

        System.out.println(WorkDay.valueOf("Mon"));

    }
}
