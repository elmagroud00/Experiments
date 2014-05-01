/* ************************************************************************
  > File Name: FirstServlet.java
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Fri Apr 18 00:12:10 2014
 *********************************************************************** */
import javax.servlet.http.*;
import javax.servlet.*;
import java.io.*;

public class FirstServlet extends HttpServlet {

    public void doGet(HttpServletRequest req, HttpServletResponse resp)
        throws ServeletException, java.io.IOException {
        
        resp.setContentType("text/html");
        resp.getWriter().print("<html>");
        resp.getWriter().print("head");
        resp.getWriter().print("</head>");
        resp.getWriter().print("body");
        resp.getWriter().print("Hello World");
        resp.getWriter().print("</body>");
        resp.getWriter().print("</html>");
    }

}
