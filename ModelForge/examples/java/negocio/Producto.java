package negocio;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Producto{

	private String nombre;
	private List<Etiqueta> etiqueta;
	private List<Posesion> posesion;
	private List<Productos_Pedido> productos_pedido;

	public Producto(String nombre) {
		this.setNombre(nombre);
		this.etiqueta = new ArrayList<Etiqueta>();
		this.posesion = new ArrayList<Posesion>();
		this.productos_pedido = new ArrayList<Productos_Pedido>();
	}

	public String getNombre() {
		return this.nombre;
	}

	public void setNombre(String nombre) {
				this.nombre = nombre;
	}

	public List<Etiqueta> getEtiqueta() {
		return Collections.unmodifiableList(this.etiqueta);
	}

	public void addEtiqueta(Etiqueta element) {
		this.etiqueta.add(element);
	}

	public void removeEtiqueta(Etiqueta element) {
		this.etiqueta.remove(element);
	}

	public List<Posesion> getPosesion() {
		return Collections.unmodifiableList(this.posesion);
	}

	public void addPosesion(Posesion element) {
		this.posesion.add(element);
	}

	public void removePosesion(Posesion element) {
		this.posesion.remove(element);
	}

	public List<Productos_Pedido> getProductos_pedido() {
		return Collections.unmodifiableList(this.productos_pedido);
	}

	public void addProductos_pedido(Productos_Pedido element) {
		this.productos_pedido.add(element);
	}

	public void removeProductos_pedido(Productos_Pedido element) {
		this.productos_pedido.remove(element);
	}

}
