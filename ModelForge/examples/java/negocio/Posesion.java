package negocio;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Posesion{

	private Integer cantidad;
	private List<Persona> poseedor;
	private List<Producto> producto;

	public Posesion(Integer cantidad) {
		this.setCantidad(cantidad);
		this.poseedor = new ArrayList<Persona>();
		this.producto = new ArrayList<Producto>();
	}

	public Integer getCantidad() {
		return this.cantidad;
	}

	public void setCantidad(Integer cantidad) {
				this.cantidad = cantidad;
	}

	public List<Persona> getPoseedor() {
		return Collections.unmodifiableList(this.poseedor);
	}

	public void addPoseedor(Persona element) {
		this.poseedor.add(element);
		element.setPosesion(this);
	}

	public void removePoseedor(Persona element) {
		this.poseedor.remove(element);
		element.setPosesion(null);
	}

	public List<Producto> getProducto() {
		return Collections.unmodifiableList(this.producto);
	}

	public void addProducto(Producto element) {
		this.producto.add(element);
		element.addPosesion(this);
	}

	public void removeProducto(Producto element) {
		this.producto.remove(element);
		element.removePosesion(this);
;
	}

}
