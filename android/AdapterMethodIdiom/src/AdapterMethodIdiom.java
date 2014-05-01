import java.util.*;

class ReversibleArrayList<T> extends ArrayList<T>{
	public ReversibleArrayList(Collection<T> c) { super(c); }
	public Iterable<T> reversed(){
		return new Iterable<T>(){
			public Iterator<T> iterator(){
				int current =  size() - 1;
				public boolean hasNext() { return current > -1; }
				public T next() { return get(current--); }
				public void remove() {
					throw new UnsupportedOperationException();
				}
			};
		}
	}
}
public class AdapterMethodIdiom {
	
}
