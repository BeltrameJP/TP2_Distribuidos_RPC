#define VERSION_NUMBER 1

struct coordenada
{
	double latitude;
	double longitude;
};

program SIMP_SERVER {
   version SIMP_VERSION {
     string CitySearch(string) = 1;
     string LatLongSearch(coordenada) = 2;
   } = VERSION_NUMBER;
} = 555555557;
