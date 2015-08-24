package com.example.sijiewang.testxcardview;

import android.animation.ObjectAnimator;
import android.animation.PropertyValuesHolder;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.support.v7.widget.CardView;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;


public class MainActivity extends ActionBarActivity {

    private RecyclerView rv = null;
    private LinearLayoutManager llm = null;
    private List<Person> persons = null;
    private RecyclerView.ItemAnimator animation = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        rv = (RecyclerView)findViewById(R.id.rv);

        llm = new LinearLayoutManager(this);
        rv.setLayoutManager(llm);

        persons = new ArrayList<Person>();
        persons.add(new Person("wangsijie"));
        persons.add(new Person("lnmcc"));
        persons.add(new Person("wangliang"));
        persons.add(new Person("wangsijie"));
        persons.add(new Person("lnmcc"));
        persons.add(new Person("wangliang"));
        persons.add(new Person("wangsijie"));
        persons.add(new Person("lnmcc"));
        persons.add(new Person("wangliang"));
        persons.add(new Person("wangsijie"));
        persons.add(new Person("lnmcc"));
        persons.add(new Person("wangliang"));
        persons.add(new Person("wangsijie"));
        persons.add(new Person("lnmcc"));
        persons.add(new Person("wangliang"));
        persons.add(new Person("wangsijie"));
        persons.add(new Person("lnmcc"));
        persons.add(new Person("wangliang"));

        RVAdapter adapter = new RVAdapter(persons);
        rv.setAdapter(adapter);

        animation = new RecyclerView.ItemAnimator() {

            @Override
            public void runPendingAnimations() {

            }

            @Override
            public boolean animateRemove(RecyclerView.ViewHolder holder) {
                return false;
            }

            @Override
            public boolean animateAdd(RecyclerView.ViewHolder holder) {
                return false;
            }

            @Override
            public boolean animateMove(RecyclerView.ViewHolder holder, int fromX, int fromY, int toX, int toY) {
                Log.d("wangsijie:", "animateMove");
                return false;
            }

            @Override
            public boolean animateChange(RecyclerView.ViewHolder oldHolder, RecyclerView.ViewHolder newHolder, int fromLeft, int fromTop, int toLeft, int toTop) {
                return false;
            }

            @Override
            public void endAnimation(RecyclerView.ViewHolder item) {

            }

            @Override
            public void endAnimations() {

            }

            @Override
            public boolean isRunning() {
                return false;
            }
        };



        rv.setItemAnimator(animation);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    class Person {
        public String name;

        Person(String _name) {
            name = _name;
        }

    }

    static class RVAdapter extends RecyclerView.Adapter<RVAdapter.PersonViewHolder> {
        List<Person> persons;

        public RVAdapter(List<Person> persons) {
            this.persons = persons;
        }

        @Override
        public PersonViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.item, parent, false);
            PersonViewHolder pvh = new PersonViewHolder(v);
            return pvh;
        }

        @Override
        public void onBindViewHolder(PersonViewHolder holder, int position) {
            holder.name.setText(persons.get(position).name);

            holder.itemView.setScaleX(0);
            holder.itemView.setScaleY(0);

            PropertyValuesHolder propx = PropertyValuesHolder.ofFloat("scaleX", 1);
            PropertyValuesHolder propy = PropertyValuesHolder.ofFloat("scaleY", 1);
            ObjectAnimator animator = ObjectAnimator.ofPropertyValuesHolder(holder.itemView, propx, propy);
            animator.setDuration(500);
            animator.start();
        }

        @Override
        public int getItemCount() {
            return persons.size();
        }

        public static class PersonViewHolder extends RecyclerView.ViewHolder {
            CardView cv;
            TextView name;

            PersonViewHolder(View itemView) {
                super(itemView);
                cv = (CardView) itemView.findViewById(R.id.cv);
                name = (TextView) itemView.findViewById(R.id.name);
            }
        }
    }
}
