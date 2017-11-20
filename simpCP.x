#define VERSION_NUMBER 1

struct coordenada_proxy
{
	double latitude;
	double longitude;
};

program SIMP_CLIENT {
   version SIMP_VERSION {
     string CitySearch_proxy(string) = 1;
     string LatLongSearch_proxy(coordenada_proxy) = 2;
   } = VERSION_NUMBER;
} = 555555556;
