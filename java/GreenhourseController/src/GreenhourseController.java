    import innerclasses.controller.*;
    
    public class GreenhourseController{
        public static void main(String[] args){
            GreenhourseControls gc = new GreenhourseControls();
            gc.addEvent(gc.new Bell(900));
            Event[] eventList = {
                gc.new ThermostatNight(0),
                gc.new LightOn(200),
                gc.new LightOff(400),
                gc.new WaterOn(600),
                gc.new WaterOff(800),
                gc.new ThermostatDay(1400)
            };
            gc.addEvent(gc.new Restart(2000, eventList));
            if(args.length == 1)
                gc.addEvent(new GreenhourseControls.Terminate(new Integer(args[0])));
            gc.run();
        }
    }
 