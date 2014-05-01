package net.lnmcc.www;

import java.io.FileInputStream;
import java.io.IOException;
import java.sql.*;
import java.util.Properties;

public class TestDB {

	public static void main(String[] args) {
		try {
			runTest();
		} catch(SQLException ex) {
			for(Throwable t : ex) {
				t.printStackTrace();
			}
		} catch(IOException ex) {
			ex.printStackTrace();
		}
	}
	
	public static void runTest() throws SQLException, IOException {
		Connection conn = getConnection();
		try {
			java.sql.Statement stat = conn.createStatement();
			stat.executeUpdate("CREATE TABLE Greetings (Message CHAR(20))");
			stat.executeUpdate("INSERT INTO Greetings VALUES ('Hello, world!')");
			
			ResultSet result = stat.executeQuery("SELECT * FROM Greetings");
			if(result.next()) {
				System.out.println(result.getString(1));
			}
			stat.executeUpdate("DROP TABLE Greetings");
		} finally {
			conn.close();
		}
	}
	
	public static Connection getConnection() throws SQLException, IOException {
		Properties props = new Properties();
		FileInputStream in = new FileInputStream("database.properties");
		props.load(in);
		in.close();
		
		String drivers = props.getProperty("jdbc.drivers");
		if(drivers != null)
			System.setProperty("jdbc.drivers", drivers);
		String url = props.getProperty("jdbc.url");
		String username = props.getProperty("jdbc.username");
		String password = props.getProperty("jdbc.password");
		
		return DriverManager.getConnection(url, username, password);
	}
}












