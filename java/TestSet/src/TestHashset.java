import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;


public class TestHashset {

    public static void main(String[] args) {
        System.out.println("Begin: " + System.currentTimeMillis());

        Set<String> aSet = new HashSet<String>();
        aSet.add("lnmcc");
        aSet.add("wang");
        aSet.add("lnmcc");
        aSet.remove("wanxxg");
        
        Iterator<String> iter = aSet.iterator();
        while(iter.hasNext()) {
            System.out.println(iter.next());
        }
        
        List<String> list = new ArrayList<String>();
        list.add("mac");
        list.add("pro");
        System.out.println(list);
        
        System.out.println("End: " + System.currentTimeMillis());
    }
}
