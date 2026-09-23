/*
 * =========================
 * TOOLLIBS SYSTEM CONTROLLER
 * =========================
 *
 * Handles:
 * - Maintenance mode
 * - Degraded mode
 * - System status validation
 * - Device registration
 */


/*
 * =========================
 * SYSTEM MODE
 * =========================
 */

async function checkSystemMode() {

  try {

    const res = await fetch(
      "./maintenance.json",
      {
        cache: "no-store"
      }
    );

    if (!res.ok) {
      throw new Error(
        `HTTP ${res.status}`
      );
    }

    const data = await res.json();

    /*
     * Validate maintenance.json.
     */

    if (
      !data ||
      typeof data.active !== "string"
    ) {

      console.warn(
        "Invalid maintenance.json, continuing normal mode"
      );

      return;
    }

    const state = data[data.active];

    if (
      !state ||
      typeof state.mode !== "string"
    ) {

      console.warn(
        "Invalid active system state, continuing normal mode"
      );

      return;
    }


    /*
     * =========================
     * MAINTENANCE
     * =========================
     */

    if (state.mode === "maintenance") {

      const code =
        state.code || "503";

      window.location.href =
        "maintenance.html?code=" +
        encodeURIComponent(code);

      return;
    }


    /*
     * =========================
     * DEGRADED
     * =========================
     */

    if (state.mode === "degraded") {

      console.warn(
        "Toollibs degraded mode:",
        state.code || "unknown"
      );

      return;
    }


    /*
     * =========================
     * NORMAL
     * =========================
     */

    if (state.mode === "normal") {

      return;
    }


    /*
     * Unknown mode.
     */

    console.warn(
      "Unknown Toollibs system mode:",
      state.mode
    );

  }

  catch (e) {

    /*
     * The maintenance system must
     * never prevent the website from
     * loading when the status service
     * itself is unavailable.
     */

    console.warn(
      "Maintenance system unavailable, continuing normal mode",
      e
    );

  }

}


/*
 * =========================
 * GLOBAL ERROR HANDLER
 * =========================
 */

window.onerror = function(message) {

  console.error(
    "Fatal error:",
    message
  );

  return false;

};


/*
 * Start system controller.
 */

checkSystemMode();


/*
 * =========================
 * DEVICE REGISTRATION
 * =========================
 */

async function registerDevice() {

  let deviceId =
    localStorage.getItem(
      "toollibs_device_id"
    );


  /*
   * Generate a persistent device ID.
   */

  if (!deviceId) {

    if (
      !window.crypto ||
      !crypto.randomUUID
    ) {

      console.warn(
        "Secure device ID generation unavailable"
      );

      return;
    }

    deviceId =
      crypto.randomUUID();

    localStorage.setItem(
      "toollibs_device_id",
      deviceId
    );

  }


  /*
   * Register device with ToollibsServer.
   */

  try {

    await fetch(
      "http://192.168.1.19:3000/register-device",
      {
        method: "POST",

        headers: {
          "Content-Type": "application/json"
        },

        body: JSON.stringify({

          id: deviceId,

          platform:
            navigator.platform,

          arch:
            navigator.userAgent

        })
      }
    );

  }

  catch (e) {

    console.error(
      "ToollibsServer device registration unavailable"
    );

  }

}


registerDevice();