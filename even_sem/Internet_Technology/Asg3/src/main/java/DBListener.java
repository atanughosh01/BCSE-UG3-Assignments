
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

/**
 * Application Lifecycle Listener implementation class DBListener
 *
 */
@WebListener
public class DBListener implements ServletContextListener {

	private String jdbcURL = "jdbc:mysql://localhost:3306/flightdb?useSSL=false";
	private String jdbcUsername = "root";
	private String jdbcPassword = "admin123";

	/**
	 * Default constructor.
	 */
	public DBListener() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see ServletContextListener#contextDestroyed(ServletContextEvent)
	 */
	public void contextDestroyed(ServletContextEvent sce) {
		// TODO Auto-generated method stub
	}

	/**
	 * @see ServletContextListener#contextInitialized(ServletContextEvent)
	 */
	public void contextInitialized(ServletContextEvent sce) {
		// TODO Auto-generated method stub

		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		sce.getServletContext().setAttribute("jdbcURL", jdbcURL);
		sce.getServletContext().setAttribute("jdbcUsername", jdbcUsername);
		sce.getServletContext().setAttribute("jdbcPassword", jdbcPassword);

	}
}
